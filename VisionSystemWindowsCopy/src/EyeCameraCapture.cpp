#include "EyeCameraCapture.h"


EyeCameraCapture::EyeCameraCapture(GUID cameraGUID, CLEyeCameraColorMode mode, CLEyeCameraResolution resolution, float fps) :
_cameraGUID(cameraGUID), _cam(NULL), _mode(mode), _resolution(resolution), _fps(fps)
{
	// Create camera instance
	_cam = CLEyeCreateCamera(_cameraGUID, _mode, _resolution, _fps);
	if(_cam == NULL) return;
	// Get camera frame dimensions
	CLEyeCameraGetFrameDimensions(_cam, _width, _height);
	// Start capturing
	CLEyeCameraStart(_cam);
}


EyeCameraCapture::~EyeCameraCapture() {
	// Stop camera capture
	CLEyeCameraStop(_cam);
	// Destroy camera object
	CLEyeDestroyCamera(_cam);
}

void EyeCameraCapture::Capture(cv::Mat& output) {
	// Ensure matrix size and type are valid
	int type = (_mode == CLEYE_COLOR_PROCESSED || _mode == CLEYE_COLOR_RAW ? CV_8UC4 : CV_8UC1);
	if (output.type() != type || output.rows != _height || output.cols != _width) {
		output.create(_height, _width, type);
	}
	CLEyeCameraGetFrame(_cam, output.data);
	
}

void EyeCameraCapture::SetCameraParameter(CLEyeCameraParameter param, int value) {
	if(!_cam) return;
	printf("CLEyeGetCameraParameter %d\n", CLEyeGetCameraParameter(_cam, (CLEyeCameraParameter)param));
	CLEyeSetCameraParameter(_cam, (CLEyeCameraParameter)param, value);
}

void EyeCameraCapture::LoadCameraParameters(std::string& file) {
	cv::FileStorage fs(file, cv::FileStorage::READ);
	SetCameraParameter(CLEYE_AUTO_GAIN, (int) fs["autoGain"]);
	SetCameraParameter(CLEYE_GAIN, (int) fs["gain"]);
	SetCameraParameter(CLEYE_AUTO_EXPOSURE, (int) fs["autoExposure"]);
	SetCameraParameter(CLEYE_EXPOSURE, (int) fs["exposure"]);
	SetCameraParameter(CLEYE_AUTO_WHITEBALANCE, (int) fs["autoWhiteBalance"]);
	SetCameraParameter(CLEYE_WHITEBALANCE_RED, (int) fs["whiteBalanceRed"]);
	SetCameraParameter(CLEYE_WHITEBALANCE_GREEN, (int) fs["whiteBalanceGreen"]);
	SetCameraParameter(CLEYE_WHITEBALANCE_BLUE, (int) fs["whiteBalanceBlue"]);
	SetCameraParameter(CLEYE_LENSCORRECTION1, (int) fs["lensCorrection1"]);
	SetCameraParameter(CLEYE_LENSCORRECTION2, (int) fs["lensCorrection2"]);
	SetCameraParameter(CLEYE_LENSCORRECTION3, (int) fs["lensCorrection3"]);
	fs.release();
}