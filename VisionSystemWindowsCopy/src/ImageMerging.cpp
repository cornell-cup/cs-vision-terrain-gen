#include "ImageMerging.h"

cv::Point2d inline applyHomography(cv::Mat h, cv::Point p) {
	cv::Mat_<double>& H = (cv::Mat_<double>) h;
	cv::Point2d out;
	double d = H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2);
	out.x = (H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2)) / d;
	out.y = (H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2)) / d;
	return out;
}

ImageMerging::ImageMerging() {
	foundChessBoard = false;
	singleCameraImage = NULL;
}

void ImageMerging::computeHomography(const cv::Mat* latestImages, const int& numimages) {
	cv::Size boardSize = cv::Size(numCornersHor, numCornersVer);
	//vector<cv::Point2f> corners[NUM_CAMERAS <= 4 ? NUM_CAMERAS : 2];
	vector<cv::Point2f> corners[4];
	
	foundChessBoard = true;

	
	// Ensure chess board found in every input image
	for (int i = 0; i < numimages; i++) {
		foundChessBoard &= cv::findChessboardCorners(latestImages[i], boardSize,
			corners[i], CV_CALIB_CB_ADAPTIVE_THRESH);
	}
	
	if (!foundChessBoard) {
		cerr << "Did you really put the chessboard there...?" << endl;
		return;
	}

	cv::namedWindow("Calibration");
	cout << "Press any key to continue..." << endl;

	// Get the coordinates of each corner of the chessboard.
	// Corners are the intersections of white and black squares.
	for (int i = 0; i < numimages; i++) {
		// Convert to grayscale
		cv::Mat grayImage;
		cv::cvtColor(latestImages[i], grayImage, CV_BGR2GRAY);
		// Get corner coordinates and store in corners[i]
		cv::cornerSubPix(grayImage, corners[i], cv::Size(4, 4), cv::Size(-1, -1),
			cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		cv::Mat image(latestImages[i].size(), latestImages[i].type());
		image = (latestImages[i]).clone();
		cv::drawChessboardCorners(image, cv::Size(BOARD_WIDTH, BOARD_HEIGHT),
			corners[i], foundChessBoard);
			cv::imshow("Calibration", image);
			cv::waitKey(0);
		}
	
	cv::destroyWindow("Calibration");

	// Generate reference frame points
	float scale = WIDTH_LENGTH * PIXELS_PER_METER;
	vector<cv::Point2f> referenceFrame;
	for(int i = numCornersVer-1; i >= 0; i--) {
		for(int j = numCornersHor-1; j >=0 ; j--) {
			referenceFrame.push_back(cv::Point(j*scale, i*scale));
		}
	}

	// Calculate homographies that transform each camera's coordinates to the reference frame
	for (int i = 0; i < numimages; i++) {
		homography[i] = cv::findHomography(referenceFrame, corners[i]);
	}
	//writeHomography("test.yml");
}

void ImageMerging::readHomography(const string& fileName, const cv::Mat* latestImages) {
	int numimages = 0;
	if (NUM_CAMERAS <= 4){
		numimages = NUM_CAMERAS;
	}
	else{
		numimages = 4;
	}
	if (1 == 2) {
		//testing
		std::string filen1 = "homography_for_2 3 4 5.yml";
		std::string filen2 = "homography_for_0 1.yml";
		cv::Mat tmp;
		cv::FileStorage fs1(filen1, cv::FileStorage::READ);
		cv::FileStorage fs2(filen2, cv::FileStorage::READ);
		char name[13];
		sprintf(name, "%s", "Homography 0");
		name[12] = '\0';		
		if (fs1.isOpened() && fs2.isOpened()) {
			for (int i = 0; i < 2; i++) {
				name[11] = '0' + i;
				homography[i] = tmp;
				homography[i+4] = tmp;
				fs1[name] >> homography[i];
				fs2[name] >> homography[i+4];
			}
			sprintf(name, "%s", "ratio");
			foundChessBoard = true;
			fs1.release();
			fs2.release();
		}
		else {
			cerr << "file " << fileName << " not found!";
			throw exception();
		}
	}
	else {
		cv::FileStorage fs(fileName, cv::FileStorage::READ);
		cv::Mat tmp;
		char name[13];
		sprintf(name, "%s", "Homography 0");
		name[12] = '\0';
		if (fs.isOpened()) {
			for (int i = 0; i < numimages; i++) {
				name[11] = '0' + i;
				homography[i] = tmp;
				fs[name] >> homography[i];
			}
			sprintf(name, "%s", "ratio");
			foundChessBoard = true;
			fs.release();
		}
		else {
			cerr << "file " << fileName << " not found!";
			throw exception();
		}
	}
}

void ImageMerging::writeHomography(const string& fileName) {
	int numimages = 0;
	if (NUM_CAMERAS <= 4){
		numimages = NUM_CAMERAS;
	}
	else{
		numimages = 4;
	}
	cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
	char name[13];
	if (fs.isOpened()) {
		for (int i = 0; i < numimages; i++) {
			sprintf(name, "Homography %d", i);
			fs << string(name) << homography[i];
		}
	}
}

void ImageMerging::fillMergeTable(ImagePointer& ptr, const int& numimages) {
	/*cv::Mat* image_ptr;
	if (numimages == 4) {
		image_ptr = &mergedImage;
	}
	else if (numimages == 2){
		image_ptr = &mergedImage2;
	}*/
	// Find the bounds of the image
	double lx = 0, hx = 0, ly = 0, hy = 0;
	for (int i = 0; i < numimages; i++) {
		cv::Mat hinv;
		cv::invert(homography[i], hinv);
		// Compute the top-left, top-right, bottom-left, and bottom-right corners
		cv::Point2d tl = applyHomography(hinv, cv::Point(0, 0));
		cv::Point2d tr = applyHomography(hinv, cv::Point(ptr.images[i].cols - 1, 0));
		cv::Point2d bl = applyHomography(hinv, cv::Point(0, ptr.images[i].rows - 1));
		cv::Point2d br = applyHomography(hinv, cv::Point(ptr.images[i].cols - 1, ptr.images[i].rows - 1));
		lx = floor(min(min(min(min(lx, tl.x), tr.x), bl.x), br.x));
		hx = ceil(max(max(max(max(hx, tl.x), tr.x), bl.x), br.x));
		ly = floor(min(min(min(min(ly, tl.y), tr.y), bl.y), br.y));
		hy = ceil(max(max(max(max(hy, tl.y), tr.y), bl.y), br.y));
	}
	//initialize output image pre-computations
	int width = hx - lx + 1, height = hy - ly + 1;
	mergedImage = (cv::Mat(cv::Size(width, height), CV_8UC4));
	//mergedImages.push_back(cv::Mat(cv::Size(width, height), CV_8UC4));

	// translation from primary image coordinates to destination (world) image coordinates
	// just a translation because primary camera image coordinates are aligned with destination world image
	int tx = (lx < 0) ? -lx : 0;
	int ty = (ly < 0) ? -ly : 0;

	// ptr.table[row][col] contains pointers into each camera image that contributes to output pixel row, col
	ptr.table = new PixelTransform*[height];
	for (int row = 0; row < height; row++) {
		ptr.table[row] = new PixelTransform[width]();
	}
	//pre-compute output image
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			PixelTransform& t = ptr.table[row][col];
			t.imgUsed = 0;
			int cam_mask = 1;
			for (int c = 0; c < numimages; c++) {
				// homography is from each camera to primary camera coordinates
				CameraPixelTransform& p = t.cam[c];
				cv::Point2d pt = applyHomography(homography[c], cv::Point(col - tx, row - ty));
				int x = (int)pt.x;
				int y = (int)pt.y;
				int inBounds = x > 0 && x < ptr.images[c].cols - 1
					&& y > 0 && y < ptr.images[c].rows - 1;
				t.imgUsed |= inBounds << c;
				// assigns alpha value in the range [0, blend_radius] , when
				// the pixel is within blend_radius of some edge of the image
				// it is given less weight in the final image pixel color
				if (t.imgUsed & cam_mask) {
					p.pixel = &(ptr.images[c].at<cv::Vec4b>(y, x));
					int alphaOptions[5] = {
						alphaBlendRadius,
						x,
						ptr.images[c].cols - x,
						y,
						ptr.images[c].rows - y
					};
					p.alphaVal = *std::min_element(alphaOptions, alphaOptions + 5);
				}
				cam_mask = cam_mask << 1;
			}
		}
	}
	// Normalize alpha values so that their sum for each pixel is (approximately) normalizedAlphaSum
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			// Compute sum
			int sum = 0;
			for (int c = 0; c < numimages; c++) {
				sum += ptr.table[row][col].cam[c].alphaVal;
			}
			if (sum == 0) sum = 1;
			// Normalize
			double scale = static_cast<double>(normalizedAlphaSum) / static_cast<double>(sum);
			for (int c = 0; c < numimages; c++) {
				CameraPixelTransform& t = ptr.table[row][col].cam[c];
				t.alphaVal = (int)(scale * t.alphaVal + 0.5); // Add 0.5 for rounding
			}
		}
	}
	
}

void ImageMerging::merge(MergeTable table, cv::Rect& roi) {
// generate combined destination image by bilinear interpolation using pixel color info from input images
// whose warped image overlaps that point

	const int nchan = 4;
	const int rowBegin = roi.y;
	const int rowEnd   = roi.y + roi.height;
	const int colBegin = roi.x;
	const int colEnd   = roi.x + roi.width;

#pragma omp parallel for  num_threads(4)

	for (int row = rowBegin; row < rowEnd; ++row) {
		cv::Vec4b* mergeRows = mergedImage.ptr<cv::Vec4b>(row);
		PixelTransform* transformRows = table[row];

		for (int col = colBegin; col < colEnd; ++col) {
			cv::Vec4b& mergePixel = mergeRows[col];
			PixelTransform& transformPixel = transformRows[col];
			unsigned int channels[nchan] = {0};

			for (int c = 0; c < NUM_CAMERAS; ++c) {
				int camMask = 1 << c;
				if (camMask & transformPixel.imgUsed) {
					CameraPixelTransform& t = transformPixel.cam[c];
					for (int k = 0; k < nchan; ++k) {
						channels[k] += t.alphaVal * (*t.pixel)[k];
					}
				}
			}
			
			for (int k = 0; k < nchan; ++k) {
				mergePixel[k] = (uchar) (channels[k] / normalizedAlphaSum);
			}
		}
	}
}

void ImageMerging::update(ImagePointer& ptr, cv::Rect& roi) {
	if (foundChessBoard) {
		merge(ptr.table, roi);
	} else {
		singleCameraImage = ptr.images;
	}
}

const cv::Mat& ImageMerging::getMergedImage() const {
	if (foundChessBoard) {
		return mergedImage;
	} else {
		return *singleCameraImage;
	}
}

cv::Mat ImageMerging::getHomography1() {
	return homography[0];
}

cv::Mat ImageMerging::getHomography2() {
	return homography[1];
}