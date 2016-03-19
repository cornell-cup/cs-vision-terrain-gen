#include <stdlib.h>
#include <vector>
#include <fstream>

#include <boost/foreach.hpp>

#include <opencv2/opencv.hpp>

#include "Vision.h"
#include "BlobResult.h"
#include "BlobTracker.h"
#include "ImageFiltering.h"
#include "ModBotKalmanFilter.h"

using namespace std;


BlobTracker::BlobTracker(const char* rgbFile, double initialTime) {
	// Set default areas and diameters
    setMinOuterBlobArea(MIN_OUTER_BLOB_AREA);
    setMaxOuterBlobArea(MAX_OUTER_BLOB_AREA);
    setMinInnerBlobArea(MIN_INNER_BLOB_AREA);
    setMaxInnerBlobArea(MAX_INNER_BLOB_AREA);

    setImageSize(cvSize(global_width, global_height));
    // Rough approx for start time
    lastCaptureTime = initialTime;
    captureTimeDiff = 1000.0 / 30.0;

    if (!readRgbColors(rgbFile)) {
    	cout << "Setting blob tracker colors to default values" << endl;
    	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
    		bgrColors[i] = DEFAULT_RGB_COLORS[i];
    	}
    }
}

bool BlobTracker::readRgbColors(const char* fileName) {
	//TODO render this function idiot proof
	ifstream f(fileName);
	if (!f.is_open()) {
		cerr << "Couldn't find file " << fileName << endl;
		return false;
	}
	int colorNumber;
	f >> colorNumber;
	if (colorNumber != NUM_SYSTEM_COLORS) {
		cerr << "Incorrect number of colors in " << fileName << endl;
		return false;
	}
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		int c1, c2, c3;
		f >> c1;
		f >> c2;
		f >> c3;
		bgrColors[i] = cvScalar(c1, c2, c3);
	}
	f.close();
	return true;
}

void BlobTracker::setImageSize(cv::Size size) {
	displayImage.create(size, CV_8UC3);
}



void BlobTracker::update(const cv::Mat* filteredImages, std::vector<cv::Rect>& windows, double captureTime) {
	// Set timing
	captureTimeDiff = (captureTime - lastCaptureTime) ;
	lastCaptureTime = captureTime;

	// Clear our knowledge of hat blobs
    pendingObjects.clear();

	// Zero out display image, giving it a black background
	displayImage = cv::Scalar(0);

	/* FIND HSV BLOBS */
	cv::Rect fullRoi(0, 0, displayImage.cols-1, displayImage.rows-1);

	BOOST_FOREACH(cv::Rect& roi, windows) {
		// Occasionally we get an empty bounding box due to fluctuations in timing that cause
		// variation in predicted bounding boxes. Empty image cause errors in cvblobslib.
		if (roi.width == 0 && roi.height == 0) { continue; }

		// iterate over colors defined in the system to generate binary images and get their blobs
		// Results are stored in "outerColorBlobResult" and "innerColorBlobResult" arrays
		for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
			cv::Mat chunk = filteredImages[i](roi).clone();
			filterBlobs(i, chunk);
		}

		// now that we have all candidate blobs for hat parts for each color
		// as filtered by size we check that outer blobs have inner blobs
		// inside then proceed with position and orientation tracking
		for (int color_j = 0; color_j < NUM_SYSTEM_COLORS; color_j++) {
			identifyBlobs(color_j, cv::Point(roi.x, roi.y));
		}

		// Append to the list of objects we've found so far
		for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
			for (int j = 0; j < colorObjects[i].size(); j++) {
				pendingObjects.push_back(colorObjects[i][j]);
			}
		}

		drawBlobs(roi);
	}

    /** UPDATE KALMAN */
	currObjectsLock.lock();
	currObjects.clear();
	kalmanFilterUpdate();
	currObjectsLock.unlock();

	// Adjust the bounding box of each blob to produce a predicted bounding box.
	// This new box tells the system where it should look for the blob in the next image.
	BOOST_FOREACH(Blob& b, currObjects) {
		cv::Rect& box = b.boundingBox;
		
		// Take the union of the current bounding box and the shifted bounding box
		int shiftX = static_cast<int>(b.velocityx * captureTimeDiff);
		int shiftY = static_cast<int>(b.velocityy * captureTimeDiff);
		box += cv::Point(shiftX, shiftY);
		
		/*
		box |= box + cv::Point(shiftX, shiftY);
		*/
		// Expand the box somewhat to increase robustness
		int expandX = max(BB_EXPAND_MIN, static_cast<int>(BB_EXPAND_MUL * box.width));
		int expandY = max(BB_EXPAND_MIN, static_cast<int>(BB_EXPAND_MUL * box.height));
		box -= cv::Point(expandX / 2, expandY / 2);
		box += cv::Size(expandX, expandY);
	}
}

void BlobTracker::filterBlobs(int i, const cv::Mat& image) {
	// Get result storage locations
	CBlobResult& outerBlobs = outerColorBlobResult[i];
	CBlobResult& innerBlobs = innerColorBlobResult[i];

	// get blobs results and filter using area

	// using knowledge of hat geometry we preserve blob candidates for
	// hat outer color and inner spot color separately

	// find blobs in image
	// The cvblobs lib only works with IplImage
	IplImage ipl = (IplImage) image;
	outerBlobs = CBlobResult(&ipl, NULL, 0);

	// begin filtering by highest expected blob reduction per property
	// computation cost, as cvblobs will only evaluate what we need to
	// know when we ask for it

	// filter first by bounding box size within some range depending on
	// hat diameter, as we know desired hat / spot area range and that
	// they are circular

	// TODO: This can be optimized a lot by going into the library and adding what we need
	// Remove width < minInnerBlobDiameter
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffX(), B_LESS, minInnerBlobDiam);
	// Remove height < minInnerBlobDiameter
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffY(), B_LESS, minInnerBlobDiam);
	// Remove width > maxOuterBlobDiameter
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffX(), B_GREATER, maxOuterBlobDiam);
	// Remove height > maxOuterBlobDiameter
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffY(), B_GREATER, maxOuterBlobDiam);
	// Remove area < minInnerBlobArea
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetArea(), B_LESS, minInnerBlobArea);
	// Remove area > maxOuterBlobArea
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetArea(), B_GREATER, maxOuterBlobArea);

	// copy others
	innerBlobs = CBlobResult(outerBlobs);

	// Remove inner blobs from set of outer blobs
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffX(), B_LESS, minOuterBlobDiam);
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffY(), B_LESS, minOuterBlobDiam);
	// Remove outer blobs from set of inner blobs
	innerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffX(), B_GREATER, maxInnerBlobDiam);
	innerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetDiffY(), B_GREATER, maxInnerBlobDiam);

	// hat blob size filtering by area to separate outer blobs
	// the size of whole hat and inner spot blobs
	outerBlobs.Filter(outerBlobs, B_EXCLUDE, CBlobGetArea(), B_LESS, minOuterBlobArea);
    innerBlobs.Filter(innerBlobs, B_EXCLUDE, CBlobGetArea(), B_GREATER, maxInnerBlobArea);
}

void BlobTracker::identifyBlobs(int color_j, cv::Point offset) {
	CBlobResult& outerBlobs = outerColorBlobResult[color_j];
	vector<Blob>& blobs = colorObjects[color_j];
	blobs.clear();

	CBlob *currentOuterBlob;
	for (int blob_j = 0; blob_j < outerBlobs.GetNumBlobs(); blob_j++) {
		currentOuterBlob = outerBlobs.GetBlob(blob_j);
		// ellipse fit to outer whole-hat size hat blob
		CvBox2D ellipse = currentOuterBlob->GetEllipse();

		// fill the spot info with the inner blob ellipse
		CvBox2D spot;
		int spotColor;

		// check for spots of any color with a center within the
		// candidate outer hat blob
		// bounding box more forgiving than CBlobGetDistanceFromPoint
		if (!findSpot(ellipse, spotColor, spot)) {
			// did not find an inner hat blob spot
			// not a true hat, skip it
			continue;
		}

		// set the raw blob properties that we know
		Blob tempBlob;
		tempBlob.innerColor = color_j; // outer color
		tempBlob.outerColor = spotColor; // inner color
		int index = tempBlob.innerColor * NUM_SYSTEM_COLORS + tempBlob.outerColor;
		tempBlob.id = index;
		tempBlob.time = lastCaptureTime; // seconds
		tempBlob.x = ellipse.center.x;
		tempBlob.y = ellipse.center.y;
		// y is inverted to accommodate image display having Y
		// increasing down the screen
		double angle = atan2(tempBlob.y - spot.center.y, spot.center.x - tempBlob.x);
		// If necessary, rotate angle to fit within 0-360 range
		if (angle > 2 * PI) angle -= 2 * PI;
		else if (angle < 0) angle += 2 * PI;
		tempBlob.orientation = angle;
		tempBlob.boundingBox = currentOuterBlob->GetBoundingBox();

		tempBlob.x += offset.x;
		tempBlob.y += offset.y;
		tempBlob.boundingBox += offset;

		blobs.push_back(tempBlob);
	}
}

bool BlobTracker::findSpot(CvBox2D& ellipse, int& color, CvBox2D& spot) {

	for (int color_i = 0; color_i < NUM_SYSTEM_COLORS; color_i++) {
		CBlobResult innerBlobs = CBlobResult(innerColorBlobResult[color_i]); // copy
		//currentInnerBlob = findSpot(color_i, innerBlobs, ellipse);

		innerBlobs.Filter(innerBlobs, B_EXCLUDE, CBlobGetXCenter(), B_OUTSIDE,
				ellipse.center.x - ellipse.size.width, ellipse.center.x + ellipse.size.width);
		innerBlobs.Filter(innerBlobs, B_EXCLUDE, CBlobGetYCenter(), B_OUTSIDE,
				ellipse.center.y - ellipse.size.height, ellipse.center.y + ellipse.size.height);

		// there is only one spot on current hats
		if (innerBlobs.GetNumBlobs() > 0) {
			// color and spot are actually outputs
			color = color_i;
			spot = innerBlobs.GetBlob(0)->GetEllipse();
			return true;
		}
	}

	return false;
}

void BlobTracker::drawBlobs(cv::Rect& roi) {
	// Define chunks to write on
	cv::Mat scratch(roi.size(), displayImage.type(), cv::Scalar(0));
	cv::Mat displayChunk(displayImage, roi);

	// The cvblobs lib only works with IplImage
	IplImage scratchImg = (IplImage) displayChunk;

	// Draw the outer blobs first
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		CBlobResult& outerBlobs = outerColorBlobResult[i];
		for (int j = 0; j < outerBlobs.GetNumBlobs(); j++) {
			outerBlobs.GetBlob(j)->FillBlob(&scratchImg, bgrColors[i]);
			cv::bitwise_or(scratch, displayChunk, displayChunk);
		}
	}

	// Then draw the smaller inner blobs over the outer blobs
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		CBlobResult& innerBlobs = innerColorBlobResult[i];
		for (int j = 0; j < innerBlobs.GetNumBlobs(); j++) {
			innerBlobs.GetBlob(j)->FillBlob(&scratchImg, bgrColors[i]);
			cv::bitwise_or(scratch, displayChunk, displayChunk);
		}
	}

	// Draw indicator lines
	BOOST_FOREACH(Blob& blob, currObjects) {
		cv::Point start(blob.x, blob.y);
		cv::Point end;

		// Draw orientation indicator line
		end.x = start.x + 30 * cos(blob.orientation);
		end.y = start.y - 30 * sin(blob.orientation); // y inverted for image display
		cv::line(displayImage, start, end, cv::Scalar(125,125,125));

		// Draw velocity indicator line
		end.x = start.x + blob.velocityx;
		end.y = start.y + blob.velocityy;
		cv::line(displayImage, start, end, cv::Scalar(255,255,0));

		// Draw bounding box
		cv::rectangle(displayImage, blob.boundingBox, cv::Scalar(0,0,255));
	}
}

const cv::Mat& BlobTracker::getImage() const {
	return displayImage;
}

const vector<Blob>& BlobTracker::getCurrObjects() const {
	return currObjects;
}


// perform a single frame update for all visible object positions using
// Kalman Filter
void BlobTracker::kalmanFilterUpdate() {
	
	//assume we missed a frame
	for (auto it = mbfkMap.begin(); it != mbfkMap.end(); ++it) {
		ModBotKalmanFilter& kf = it->second;
		kf.nFramesMissed++;
	}

	// Update the KFs for the blobs we've found
	BOOST_FOREACH(Blob& b, pendingObjects) {
		// If the kalman filter doesn't already exist, it is constructed by the [] operator
		ModBotKalmanFilter& kf = mbfkMap[b.id];
		// Occasionally two bounding boxes overlap and contain the same blob. In this case we only
		// want to update the kalman filter once, so we detect that is has already been updated by
		// checking that nFramesMissed is 0.
		if (kf.nFramesMissed == 0) { continue; }
		// If a blob has been lost for too long, we reset its kalman filter.
		if (kf.nFramesMissed > 3) { kf = ModBotKalmanFilter(); }
		kf.update(b, captureTimeDiff);
		kf.nFramesMissed = 0;
		currObjects.push_back(b);
	}

	// For each blob that we can't find anymore, either predict its location or
	// stop tracking it entirely.
	auto it = mbfkMap.begin();
	while(it != mbfkMap.end()) {
		ModBotKalmanFilter& kf = it->second;
		if (kf.nFramesMissed > 10) {
			// Blob has been missing too long, so we delete it
			mbfkMap.erase(it++);
		} else if (kf.nFramesMissed > 0){
			// We've lost the blob a short period of time, so we keep tracking it by predicting
			// its location and expanding its bounding box quadratically
			kf.blobNotFound(captureTimeDiff);
			Blob& b = kf.blob;
			cv::Rect& box = b.boundingBox;

			// Occasionally we'll get a random bounding box appearing at (0,0). Not sure why,
			// but this seems to fix it.
			if (b.x == 0 && b.y == 0) { continue; }

			// Shift box according to velocity * time
			int shiftX = static_cast<int>(b.velocityx * captureTimeDiff);
			int shiftY = static_cast<int>(b.velocityy * captureTimeDiff);
			box += cv::Point(shiftX, shiftY);

			// Expand the box to increase chance of finding it
			int expandX = kf.nFramesMissed * 5;
			int expandY = kf.nFramesMissed * 5;
			box -= cv::Point(expandX / 2, expandY / 2);
			box += cv::Size(expandX, expandY);

			currObjects.push_back(kf.blob);
			++it;
		} else {
			// Blob was found in last frame, so the kf has already been updated
			++it;
		}
	}
}

int areaToDiameter(int area) {
	return (int) (sqrt((4 * area)/PI));
}

void BlobTracker::setMinOuterBlobArea(int value) {
	minOuterBlobArea = value;
    minOuterBlobDiam = areaToDiameter(value);
}

void BlobTracker::setMaxOuterBlobArea(int value) {
	maxOuterBlobArea = value;
    maxOuterBlobDiam = areaToDiameter(value);
}

void BlobTracker::setMinInnerBlobArea(int value) {
	minInnerBlobArea = value;
    minInnerBlobDiam = areaToDiameter(value);
}

void BlobTracker::setMaxInnerBlobArea(int value) {
	maxInnerBlobArea = value;
    maxInnerBlobDiam = areaToDiameter(value);
}
