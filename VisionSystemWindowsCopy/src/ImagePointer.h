#ifndef IMAGEPOINTER_H_
#define IMAGEPOINTER_H_
#include <opencv2/core/core.hpp>
#include "Vision.h"
#include "Timer.h"

/** Data that corresponds to a single pixel in a camera image. */
struct CameraPixelTransform {
	const cv::Vec4b* pixel;
	/** Value in range [0, alphaBlendRadius] which weights the contribution
		*  of this camera pixel to the merged image */
	int alphaVal;
};

/** Data that corresponds to a single pixel in each camera image. */
struct PixelTransform {
	/** A bit vector, where a 1 in position i means cam[i] contributes
		* color to this output pixel. */
	int imgUsed;
	/** Array of camera pixels which contribute to this output pixel */
	CameraPixelTransform cam[NUM_CAMERAS];
};
	
/**
	* Type of lookup table for speeding up image merging. Each pixel mergedImage[row][col] has a
	* corresponding matrix entry transform[row][col].
	*/
typedef PixelTransform** MergeTable;

/**
* A class to store a set of camera images and their associated MergeTable
*/
struct ImagePointer {
	cv::Mat images[NUM_CAMERAS];
	MergeTable table;
	Timer timer;
};


#endif