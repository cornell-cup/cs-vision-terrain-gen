#pragma once

#include "CLEyeMulticam.h"
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>

/**
 * This class represents a single PS3 Eye camera. It can be used to capture the camera's video
 * stream as a series of images.
 */
class EyeCameraCapture {
private:
	/** Globally Unique Identifier for this camera */
	GUID _cameraGUID;

	/** The camera instance used internally by the CLEye library */
	CLEyeCameraInstance _cam;

	/** The color mode of this camera */
	CLEyeCameraColorMode _mode;

	/** The resolution of this camera */
	CLEyeCameraResolution _resolution;

	/** The width of the camera image, int pixels */
	int _width;

	/** The height of the camera image, in pixels */
	int _height;

	/** The frames per second of this camera */
	float _fps;

public:
	/** 
	 * Initializes a new camera capture.
	 * 
	 * @param cameraGUID The GUID of the camera to use, as fetched by CLEyeGetCameraUUID
	 * @param mode The color mode of this camera
	 * @param resolution The resolution of this camera
	 * @param fps The frames per second of this camera
	 */
	EyeCameraCapture(GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps);
	
	/**
	 * Capture a single frame, and write it to the given output Mat
	 * @param output The matrix to write the image to. It is resized if necessary.
	 */
	void Capture(cv::Mat& output);

	/**
	 * Sets a camera parameter to a given value.
	 * @param param The parameter to modify
	 * @param value The value to set the parameter
	 */
	void SetCameraParameter(CLEyeCameraParameter param, int value);
	
	/**
	 * Load camera parameters from a file.
	 * @param file The parameters file
	 */
	void LoadCameraParameters(std::string& file);
	
	/** Destroy this instance */
	~EyeCameraCapture();

};

