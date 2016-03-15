#include <opencv2/opencv.hpp>
#include <fstream>

#include "Vision.h"
#include "HsvColorRange.h"
#include "ImageFiltering.h"

using namespace cv;
using namespace std;
/** Color ranges in which blobs are found */

ImageFiltering::ImageFiltering(const char* hsvFile) {
	// Try to read from file, use defaults on failure
	if (!readColors(hsvFile)) {
		cout << "Setting filter colors to default values" << endl;
		for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
			systemColors[i] = DEFAULT_HSV_RANGES[i];
		}
	}
//set the range for each color
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		if (systemColors[i].h.hi < systemColors[i].h.lo) {
			hsv_min1[i] = Scalar(0, systemColors[i].s.lo,
					systemColors[i].v.lo, 0);
			hsv_max1[i] = Scalar(systemColors[i].h.hi, systemColors[i].s.hi,
					systemColors[i].v.hi, 0);
			hsv_min2[i] = Scalar(systemColors[i].h.lo, systemColors[i].s.lo,
					systemColors[i].v.lo, 0);
			hsv_max2[i] = Scalar(255, systemColors[i].s.hi,
					systemColors[i].v.hi, 0);
		} else {
			hsv_min1[i] = Scalar(
					MIN(systemColors[i].h.lo,systemColors[i].h.hi),
					systemColors[i].s.lo, systemColors[i].v.lo, 0);
			hsv_max1[i] = Scalar(
					MAX(systemColors[i].h.lo,systemColors[i].h.hi),
					systemColors[i].s.hi, systemColors[i].v.hi, 0);
		}
	}
	//initialize a space to store the color converted image
	filteredImage= cv::Mat(cv::Size(1, 1), CV_8UC3);
}

bool ImageFiltering::readColors(const char* fileName) {
	int colorNumber;
	int temp;
	ifstream f;
	f.open(fileName);
	f >> colorNumber;
	if (!f.is_open() || colorNumber != NUM_SYSTEM_COLORS) {
		cerr << "File not found or number of system colors mismatch" << endl;
		return false;
	}
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		f >> temp;
		if ((temp + colorRange) <= 255)
			systemColors[i].h.hi = temp + colorRange;
		else
			systemColors[i].h.hi = temp + colorRange - 255;
		if ((temp - colorRange) >= 0)
			systemColors[i].h.lo = temp - colorRange;
		else
			systemColors[i].h.lo = temp - colorRange + 255;
	}
	f.close();
	return true;
}

void ImageFiltering::resize(const cv::Mat& mergedImage) {
	if(filteredImage.size()!=mergedImage.size()){
		filteredImage.create(mergedImage.size(),CV_8UC3);
		for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
			colorThresh[i].create(mergedImage.size(), CV_8U);
			colorThresh2[i].create(mergedImage.size(), CV_8U);
		}
	}
}

void ImageFiltering::filter(const cv::Mat& mergedImage, const cv::Rect& roi) {
	resize(mergedImage);
	cv::Mat& mergedRoi = mergedImage(roi);
	cv::Mat& filterRoi = filteredImage(roi);
	cv::cvtColor(mergedRoi, filterRoi, CV_BGR2HSV);// convert color from rgb to hsv

#pragma omp parallel for num_threads(NUM_SYSTEM_COLORS)
	for (int i = 0; i < NUM_SYSTEM_COLORS; i++) {
		cv::Mat& threshRoi = colorThresh[i](roi);
		// sometimes hue can wrap around (red objects)
		if (systemColors[i].h.hi < systemColors[i].h.lo) {
			cv::Mat& threshRoi2 = colorThresh2[i](roi);
			// Get hues between 0 and hhigh
			inRange(filterRoi, hsv_min1[i], hsv_max1[i], threshRoi);
			// Get hues between hlow and 255
			inRange(filterRoi, hsv_min2[i], hsv_max2[i], threshRoi2);
			// Bitwise-or them
			cv::bitwise_or(threshRoi, threshRoi2, threshRoi);
		} else {
			// the usual hsv thresholding
			cv::inRange(filterRoi, hsv_min1[i], hsv_max1[i], threshRoi);
		}
		
	}
}

const Mat& ImageFiltering::getFilteredImage(int i) {
	return colorThresh[i];
}

const Mat* ImageFiltering::getFilteredImages() {
	return colorThresh;
}
