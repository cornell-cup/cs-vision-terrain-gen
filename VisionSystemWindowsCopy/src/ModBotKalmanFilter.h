/*
 * ModBotKalmanFilter.h
 *
 *  Created on: Nov 8, 2012
 *      Author: rh651-01user
 */

#ifndef MODBOTKALMANFILTER_H_
#define MODBOTKALMANFILTER_H_

#include <math.h>

#include "opencv2/video/tracking.hpp"
#include "Blob.h"

/**
 * This class implements Kalman filters for modbots, using openCV's Kalman filters.
 */
class ModBotKalmanFilter {
private:
	cv::KalmanFilter positionKF, rotationKF;
	cv::Mat positionState,rotationState;

public:
	/* The number of frames ago the blob corresponding to this KF was last seen. */
	int nFramesMissed;

	Blob blob;

	/**
	 * This constructor initializes all the necessary matrices to have a good Kalman filter for a ModBot
	 */
	ModBotKalmanFilter();

	/**
	 * Perform the update of the Kalman filter: does both prediction and correction steps
	 * @param measurement A blob containing position and orientation as measured in the image
	 * @param timeDiffSec time since the last measurement was made, in seconds
	 */
	void update(Blob& measurement, double timeDiffSec);

	void blobNotFound(double timeDiffSec);

	/**
	 * get the current state of the kalman filter
	 * @param blob function modifies position, orientation and velocities to be estimates of the truth (other fields not modified...)
	 */
	 void getState(Blob & blob);
};

#endif /* MODBOTKALMANFILTER_H_ */
