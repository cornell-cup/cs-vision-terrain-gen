/*
 * ImageMerging.h
 *
 *  Created on: Oct 16, 2012
 *      Author: rh651-01user
 */

#ifndef IMAGEMERGING_H_
#define IMAGEMERGING_H_

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 5
#define WIDTH_LENGTH 0.0541

#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Vision.h"
#include "ImagePointer.h"

using namespace std;

/** This class takes care of the merging of images.
* It is designed for a fixed number of cameras
*/
class ImageMerging {
private:
	/** Some parameters for the chessboard detection */
	static const int numCornersHor = BOARD_WIDTH, numCornersVer = BOARD_HEIGHT;
	/** This value is used to assign an alpha value */
	static const int alphaBlendRadius = 10;
	/** The sum of the normalized alpha values for each pixel. This should be a power of 2. */
	static const unsigned int normalizedAlphaSum = 2048;
	/** Contains the image once it has been merged */
	//cv::Mat mergedImage;
	std::vector<cv::Mat> mergedImages;

	/** A pointer to the image of the first camera */
	const cv::Mat* singleCameraImage;
	
	cv::Mat homography[NUM_CAMERAS+3];

	//testing
	cv::Mat homography_test[5];
	
	/**
	* Perform the merging. This function is supposed to be highly optimized.
	* @param latestImages contains the images from the cameras, as given by the CameraHandler class.
	* @param rowPointers contains row pointers for the cameras images, as given by the CameraHandler class.
	*/
	void merge(std::vector<MergeTable> table, cv::Rect& roi, int index);

public:
	
	/** Constructor 
	* Does not initialize the merging.
	*/
	ImageMerging();
	
	/** Flag to see if the system was initialized or not */
	bool foundChessBoard;

	/**
	* This function is used to initialize the "transform" lookup table once the homographies have been computed or loaded from file.
	* @param latestImages contains the images from the cameras, as given by the CameraHandler class.
	*/
	void fillMergeTable(ImagePointer& ptr, const int& numimages, std::vector<int> merge_ints, int index);

	/**
	* Detect the chessboard and pre compute the necessary variables (homographies). 
	* Outputs a message to cout if did not find the chessboard. Otherwise sets foundChessBoard to true.
	* @param latestImages contains the images from the cameras, as given by the CameraHandler class.
	* @param rowPointers contains row pointers for the cameras images, as given by the CameraHandler class.
	* @see readHomography()
	* @see writeHomography()
	*/
	void computeHomography(const cv::Mat* images, int& numimages, std::vector<int> merge_ints);
	
	/**
	* Load homographies from file. 
	* @param fileName the path to the file containing the homography information (OpenCV yml or xml format)
	* @param latestImages contains the images from the cameras, as given by the CameraHandler class.
	* @see computeHomography()
	* @see writeHomography()
	*/
	void readHomography(const string& fileName,  const cv::Mat* latestImages);
	
	/**
	* Perform an update: perform a merging if the system has been initialized (through computeHomography or readHomography)
	* @param latestImages contains the images from the cameras, as given by the CameraHandler class.
	* @param rowPointers contains row pointers for the cameras images, as given by the CameraHandler class.
	* @see computeHomography()
	* @see readHomography()
	*/
	void update(ImagePointer& ptr, cv::Rect& roi, int index);
	
	/**
	* Write homographies to a file on disk. This info will be reused by the computeHomography function. 
	* Homographies must have been loaded from disk or computed.
	* @param fileName the name of the file to be written on. Use .yml or .xml extension.
	* @see computeHomography()
	* @see readHomography()
	*/
	void writeHomography(const string& fileName);
	
	/**
	* Get the merged image as a const reference.
	* @return a reference to the merged image
	*/
	const std::vector<cv::Mat> getMergedImage() const;
	
	/**
	* Get the homography.
	* @return homography
	*/
	cv::Mat getHomography1();

	cv::Mat getHomography2();
};

#endif /* IMAGEMERGING_H_ */
