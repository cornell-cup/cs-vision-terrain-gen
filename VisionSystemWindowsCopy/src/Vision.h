#ifndef VISION_H_
#define VISION_H_

#include <string>
#include <math.h>
#include <opencv2/opencv.hpp>

#include "HsvColorRange.h"

// ===== Global constants ===== //

const unsigned int NUM_CAMERAS = 6;		// number of overhead cameras to use

const unsigned int NUM_BLOBS = 1;		// number of robots to track

const double PIXELS_PER_METER = 250;	// magical pixel-to-meter conversion factor

/** Number of hat colors recognized by the vision system */
const int NUM_SYSTEM_COLORS = 2;

/** Default color ranges; used when hsv file not found */
const HsvColorRange DEFAULT_HSV_RANGES[] = {
		HsvColorRange("red",  165,  15, 50, 255, 30, 255),
		HsvColorRange("green", 22,  91, 40, 255, 30, 255),
		HsvColorRange("blue",  92, 150, 82, 255, 30, 255)
};

const HsvColorRange DEFAULT_HLS_RANGES[] = {
		HsvColorRange("red",  165,  12, 0, 255, 0, 255),
		HsvColorRange("green", 30,  91, 0, 255, 0, 255),
		HsvColorRange("blue",  92, 150, 0, 255, 0, 255)
};

/** Default colors; used when rgb file not found */
const CvScalar DEFAULT_RGB_COLORS[] = {
		cvScalar(0,0,255),
		cvScalar(0,255,0),
		cvScalar(255,0,0)
};

const double BB_EXPAND_MUL = 0.5;
const int    BB_EXPAND_MIN = 10;

/** Size of the kalman filter history */
const int HIST_SIZE = 6;
/** Maximum number of hat blobs */
const int MAX_OBJECTS = 64;
/** camera image width size for each camera */
const int global_width = 640;
/** camera image height size for each camera */
const int global_height = 480;

/** PI */
const double PI=3.14159265359;

/** Default values for blob area */
// Make sure ranges are not overlapping!
const int MIN_OUTER_BLOB_AREA = 550;
const int MAX_OUTER_BLOB_AREA = 8000;
const int MIN_INNER_BLOB_AREA = 100;
const int MAX_INNER_BLOB_AREA = 500;

/** Default file to which homography data is written */
const char* const HOMOGRAPHY_FILE = "offset.yml";

/** Default files to which rgb and hsv data is written */
const char* const RGB_FILE = "rgb.txt";
const char* const HSV_FILE = "hsv.txt";

/** Default file to which modbot tracking data is logged */
const char* const LOG_FILE = "data.txt";

#endif /* VISION_H_ */

