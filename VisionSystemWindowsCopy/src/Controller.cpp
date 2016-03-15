#include <stdio.h>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <limits>

#include "Vision.h"
#include "BlobTracker.h"
#include "Controller.h"
#include "ImageMerging.h"

// Controller associated window names
const string Controller::BLOB_SIZE_WINDOW = "Blob Area Constraints";

/**
 * Constructs a new Controller object
 *
 * @param c The CameraHandler object
 * @param m The ImageMerging object
 * @param f the ImageFiltering object
 * @param t the BlobTracker object
 */
Controller::Controller(CLEyeHandler* c, ImageMerging* m, ImageFiltering* f, BlobTracker* t) :
		cameras(c), merger(m), filter(f), tracker(t), k1(0), k2(0), k3(0), logEnabled(false) {

    minOuterBlobArea = &(t->minOuterBlobArea);
	maxOuterBlobArea = &(t->maxOuterBlobArea);
	minInnerBlobArea = &(t->minInnerBlobArea);
	maxInnerBlobArea = &(t->maxInnerBlobArea);

	setMinOuterBlobArea = boost::bind(&BlobTracker::setMinOuterBlobArea, t, _1);
	setMaxOuterBlobArea = boost::bind(&BlobTracker::setMaxOuterBlobArea, t, _1);
	setMinInnerBlobArea = boost::bind(&BlobTracker::setMinInnerBlobArea, t, _1);
	setMaxInnerBlobArea = boost::bind(&BlobTracker::setMaxInnerBlobArea, t, _1);
}

/**
 * Computes a homography for the camera configuration using the checkerboard method.
 *
 * Triggered by the 'o' key, which stands for "Offset calculation"
 */
void Controller::computeHomography() {
	// Fill the MergeTable for both sets of images
	ImagePointer* ptr = cameras->pipeline.readRequest();

	if (NUM_CAMERAS <= 4) {
		merger->computeHomography(ptr->images, NUM_CAMERAS);
		cameras->pipeline.readRelease();

		if (merger->foundChessBoard) {

			merger->fillMergeTable(*ptr, NUM_CAMERAS);
			merger->fillMergeTable(*cameras->pipeline.readRequest(), NUM_CAMERAS);
			cameras->pipeline.readRelease();
			tracker->setImageSize(merger->getMergedImage().size());
		}
	}
	else {
		std::cout << "WARNING: this is a testing merge case. This isn't supposed to be real" << endl;
		std::cout << "Input the number of cameras you want to merge..." << endl;
		string num_merge = "";
		std::getline(std::cin, num_merge);
		int num_merge_int = atoi(num_merge.c_str());
		std::vector<int> camera_num(num_merge_int);
		
		cv::Mat temp_image[4];

		std::cout << "Input the camera numbers you want to merge seperated by a space..." << endl;
		std::getline(std::cin, num_merge);

		istringstream iss(num_merge);
		string s;
		int i = 0;
		while (getline(iss, s, ' ')) {
			camera_num.at(i) = atoi(s.c_str());
			i++;	
		}

		for (int i = 0; i < num_merge_int; i++) {
			temp_image[i] = ptr->images[i];
			ptr->images[i] = ptr->images[camera_num.at(i)];

		}

		merger->computeHomography(ptr->images, num_merge_int);

		for (int i = 0; i < num_merge_int; i++) {
			ptr->images[i] = temp_image[i];
		}

		cameras->pipeline.readRelease();
		if (merger->foundChessBoard) {
			for (int i = 0; i < num_merge_int; i++) {
				temp_image[i] = ptr->images[i];
				ptr->images[i] = ptr->images[camera_num.at(i)];

			}

			merger->fillMergeTable(*ptr, num_merge_int);

			for (int i = 0; i < num_merge_int; i++) {
				ptr->images[i] = temp_image[i];
			}

			ImagePointer* ptr2 = cameras->pipeline.readRequest();

			for (int i = 0; i < num_merge_int; i++) {
				temp_image[i] = ptr2->images[i];
				ptr2->images[i] = ptr2->images[camera_num.at(i)];

			}

			merger->fillMergeTable(*ptr2, num_merge_int);

			for (int i = 0; i < num_merge_int; i++) {
				ptr2->images[i] = temp_image[i];
			}

			cameras->pipeline.readRelease();
			tracker->setImageSize(merger->getMergedImage().size());

			merger->writeHomography("homography_for_" + num_merge + ".yml");
		}
	}
}

/**
 * Reads in and applies a homography from the HOMOGRAPHY_FILE defined in Vision.h.
 *
 * Triggered by the 'r' key.
 */
void Controller::readHomography() {
	// Fill the MergeTable for both sets of images
	ImagePointer* ptr = cameras->pipeline.readRequest();
	merger->readHomography(HOMOGRAPHY_FILE, ptr->images);
	cameras->pipeline.readRelease();
	if (merger->foundChessBoard) {
		merger->fillMergeTable(*ptr, NUM_CAMERAS);
		merger->fillMergeTable(*cameras->pipeline.readRequest(), NUM_CAMERAS);
		cameras->pipeline.readRelease();
		tracker->setImageSize(merger->getMergedImage().size());
	}
}

/**
 * Writes the current homography to the HOMOGRAPHY_FILE defined in Vision.h
 *
 * Triggered by the 'w' key.
 */
void Controller::writeHomography() {
	merger->writeHomography(HOMOGRAPHY_FILE);
	tracker->setImageSize(merger->getMergedImage().size());
}

/**
 * Utilizes callbacks to update blob area threshold values
 */
void runCallback(int value, void* callback) {
	Controller::AreaCallback* cb = (Controller::AreaCallback*) callback;
	(*cb)(value);
}

/**
 * Shows a settings window for modifying blob size thresholds.
 *
 * Triggered by the 'q' key.
 */
void Controller::showBlobSizeWindow() {
	cv::namedWindow(BLOB_SIZE_WINDOW);
	// Create a trackbar for each area setting
	// The callbacks must be passed in as as the "void* userData" because they are pointers
	// to object methods. This prevents them from being called directly.
	cv::createTrackbar("Min Outer", BLOB_SIZE_WINDOW, minOuterBlobArea, 1000,
			runCallback, (void*) &setMinOuterBlobArea);
	cv::createTrackbar("Max Outer", BLOB_SIZE_WINDOW, maxOuterBlobArea, 10000,
			runCallback, (void*) &setMaxOuterBlobArea);
	cv::createTrackbar("Min Inner", BLOB_SIZE_WINDOW, minInnerBlobArea, 1000,
			runCallback, (void*) &setMinInnerBlobArea);
	cv::createTrackbar("Max Inner", BLOB_SIZE_WINDOW, maxInnerBlobArea, 10000,
			runCallback, (void*) &setMaxInnerBlobArea);
}

/**
 * Toggles data logging
 *
 * Triggered by the 'l' key.
 */
void Controller::toggleLogging() {
	logEnabled = !logEnabled;
}

/**
 * Indicates to Vision.cpp whether or not data logging should occur
 */
bool Controller::shouldLog() {
	return logEnabled;
}

/**
 * Adjusts camera lens correction variables by a specified offset. 
 *
 * The following keys adjust the lens correction variables as follows:
 * '7' / '4  : Increase / Decrease k1 by 1
 * '8' / '5' : Increase / Decrease k2 by 1
 * '9' / '6' : Increase / Decrease k3 by 1
 */
void Controller::adjustLensCorrection(CLEyeCameraParameter p, int change) {
	switch (p) {
	case CLEYE_LENSCORRECTION1 :
		k1 += change;
		cameras->setParam(p, k1);
		break;
	case CLEYE_LENSCORRECTION2 :
		k2 += change;
		cameras->setParam(p, k2);
		break;
	case CLEYE_LENSCORRECTION3 :
		k3 += change;
		cameras->setParam(p, k3);
		break;
	}
}