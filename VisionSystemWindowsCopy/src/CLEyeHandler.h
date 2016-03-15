#pragma once

#include "CLEyeMulticam.h"
#include <vector>
#include <string>
#include <boost/thread.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include "EyeCameraCapture.h"
#include "ImagePointer.h"
#include "PipelineManager.h"

/**
 * Handles concurrent capturing of camera images.
 */
class CLEyeHandler {
public:

	/**
	* Constructor... Throws an exception if couldn't open the cameras
	* @param camId a vector containing the camera ids to be used, usually [0,1,2,3]
	*/
	CLEyeHandler(const std::vector<int>& camIds);

	/**
	 * http://cdn.memegenerator.net/instances/400x/20498265.jpg
	 */
	virtual ~CLEyeHandler(void);

	/**
	 * Sets the value of a CLEye camera parameter for every camera.
	 */
	void setParam(CLEyeCameraParameter param, int value);

	/**
	* Call this function to update the outputs by retrieving new images from the cameras.
	*/
	void update(cv::Mat* outputs);

	/**
	 * Image pipeline. This pipeline contains two sets of images, which are alternately written to.
	 * While one set is being written, the other can be read by the system. Call
	 * pipeline.readRequest() to get an ImagePointer, and pipeline.readRelease() when the images
	 * are no longer needed.
	 */
	PipelineManager<ImagePointer> pipeline;

private:
	/** An array of pointers to EyeCameraCapture. Used for capturing images. */
	EyeCameraCapture** captures;

	/**
	 * The thread which captures images. Sets of captured images are put into the pipeline, and can
	 * be retrieved by CLEyeHandler::pipeline::readRequest().
	 */
	boost::thread* captureThread;

	/* Method run by captureThread to continuously capture images. */
	void runCaptureLoop();
};

