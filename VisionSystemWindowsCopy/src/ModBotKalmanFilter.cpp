/*
 * ModBotKalmanFilter.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: rh651-01user
 */

#include "ModBotKalmanFilter.h"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include "Blob.h"
#include "Vision.h"

using namespace std;
/**
* Simple rounding function
*/
double round(double r) {
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

/**
* Sometimes angles can jump from 2Pi to 0, so we need to filter these out
*
*/
double filterAngle(double first, double second) {

    double difference = first - second;
	return (round(difference/(2*PI))*2*PI + second);
}




ModBotKalmanFilter::ModBotKalmanFilter() {
	positionKF=cv::KalmanFilter(4,2,0);
	rotationKF=cv::KalmanFilter(2,1,0);
	positionState=cv::Mat(4, 1, CV_32F); //(x,y,dx,dy)
	rotationState=cv::Mat(2, 1, CV_32F); //(theta,dtheta)
	positionKF.transitionMatrix = *(cv::Mat_<float>(4, 4) << 1,0,0.0333,0,
															 0,1,0,0.0333,
															 0,0,1,0,
															 0,0,0,1);
	rotationKF.transitionMatrix = *(cv::Mat_<float>(2, 2) << 1, 0.0333, 0, 1);
	cv::setIdentity(positionKF.measurementMatrix);
	positionKF.processNoiseCov= *(cv::Mat_<float>(4, 4) <<
			 1e-7,0,1e-5,0,
			 0,1e-7,0,1e-5,
			 1e-5,0,1e-3,0,
			 0,1e-5,0,1e-3); //defined as in the truck example in the wikipedia page, based on multivariate normal distribution for the accceleration...
	positionKF.processNoiseCov*=350;
	cv::setIdentity(positionKF.measurementNoiseCov, cv::Scalar::all(0.005));
	cv::setIdentity(positionKF.errorCovPost, cv::Scalar::all(10)); //initialize to large number L to say we don't know the inital position 

	cv::setIdentity(rotationKF.measurementMatrix);
	rotationKF.processNoiseCov=*(cv::Mat_<float>(2, 2) << 1e-7, 1e-5, 1e-5, 1e-3);
	rotationKF.processNoiseCov*=200;
	cv::setIdentity(rotationKF.measurementNoiseCov, cv::Scalar::all(0.1));
	cv::setIdentity(rotationKF.errorCovPost, cv::Scalar::all(10));
	// Initialized to one so that
	nFramesMissed=1;

}

void ModBotKalmanFilter::update(Blob& blobMeasurement,double timeDiffSec) {
	positionKF.transitionMatrix =
			*(cv::Mat_<float>(4, 4) << 1, 0, timeDiffSec, 0, 0, 1, 0, timeDiffSec, 0, 0, 1, 0, 0, 0, 0, 1);

	cv::Mat positionMeasurement(2, 1, CV_32F);
	positionMeasurement.at<float>(0,0)=blobMeasurement.x;
	positionMeasurement.at<float>(1,0)=blobMeasurement.y;
	positionKF.predict();
	positionKF.correct(positionMeasurement);
	
	rotationKF.transitionMatrix = *(cv::Mat_<float>(2, 2) << 1,timeDiffSec , 0, 1);
	const cv::Mat& rotationPrediction = rotationKF.predict();
	cv::Mat rotationMeasurement(1, 1, CV_32F);
	rotationMeasurement.at<float>(0,0)=filterAngle(rotationPrediction.at<float>(0,0),blobMeasurement.orientation);
	rotationKF.correct(rotationMeasurement);

	blobMeasurement.x=positionKF.statePost.at<float>(0);
	blobMeasurement.y=positionKF.statePost.at<float>(1);
	blobMeasurement.velocityx=positionKF.statePost.at<float>(2);
	blobMeasurement.velocityy=positionKF.statePost.at<float>(3);
	blobMeasurement.orientation=rotationKF.statePost.at<float>(0);
	blobMeasurement.velocityRot=rotationKF.statePost.at<float>(1);
	blob=blobMeasurement;
}

void ModBotKalmanFilter::blobNotFound(double timeDiffSec) {
	positionKF.transitionMatrix = *(cv::Mat_<float>(4, 4) << 
		1, 0, timeDiffSec, 0, 
		0, 1, 0, timeDiffSec,
		0, 0, 1, 0,
		0, 0, 0, 1);
	const cv::Mat& positionPrediction = positionKF.predict();

	rotationKF.transitionMatrix = *(cv::Mat_<float>(2, 2) << 1, timeDiffSec , 0, 1);
	rotationKF.predict();
	
	positionKF.statePost=positionKF.statePre;
	rotationKF.statePost=rotationKF.statePre;
	blob.x=positionKF.statePre.at<float>(0);
	blob.y=positionKF.statePre.at<float>(1);
	blob.velocityx=positionKF.statePre.at<float>(2);
	blob.velocityy=positionKF.statePre.at<float>(3);
	blob.orientation=rotationKF.statePre.at<float>(0);
	blob.velocityRot=rotationKF.statePre.at<float>(1);
}


void ModBotKalmanFilter::getState(Blob& _blob) {
	
	_blob.x=positionKF.statePost.at<float>(0);
	_blob.y=positionKF.statePost.at<float>(1);
	_blob.velocityx=positionKF.statePost.at<float>(2);
	_blob.velocityy=positionKF.statePost.at<float>(3);
	_blob.orientation=rotationKF.statePost.at<float>(0);
	_blob.velocityRot=rotationKF.statePost.at<float>(1);
	blob=_blob;
}