#include "CLEyeHandler.h"

CLEyeHandler::CLEyeHandler(const std::vector<int>& camIds) {
	// Create camera captures
	captures = new EyeCameraCapture*[NUM_CAMERAS];
	for(int i = 0; i < NUM_CAMERAS; i++) {
		// Query unique camera uuid
		GUID guid = CLEyeGetCameraUUID(i);
		printf("Camera %d GUID: [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]\n", 
						i+1, guid.Data1, guid.Data2, guid.Data3,
						guid.Data4[0], guid.Data4[1], guid.Data4[2],
						guid.Data4[3], guid.Data4[4], guid.Data4[5],
						guid.Data4[6], guid.Data4[7]);

		captures[i] = new EyeCameraCapture(guid, CLEYE_COLOR_PROCESSED, CLEYE_VGA, 60);
		captures[i]->LoadCameraParameters(std::string("eyeconfig.yml"));
	}

	// Begin concurrent capturing
	captureThread = new boost::thread(&CLEyeHandler::runCaptureLoop, this);
}

CLEyeHandler::~CLEyeHandler() {
	for (int i = 0; i < NUM_CAMERAS; i++) {
		printf("Stopping capture on camera %d\n", i);
		delete captures[i];
	}
}


void CLEyeHandler::update(cv::Mat* outputs) {
#pragma omp parallel for num_threads(4)
	for (int i = 0; i < NUM_CAMERAS; i++) {
		captures[i]->Capture(outputs[i]);
	}
}

void CLEyeHandler::runCaptureLoop() {
	while (true) {
		ImagePointer* ptr = pipeline.writeRequest();
		ptr->timer.start();
		update(ptr->images);
		pipeline.writeRelease();
	}
}

void CLEyeHandler::setParam(CLEyeCameraParameter param, int v) {
	for (int i = 0; i < NUM_CAMERAS; i++) {
			captures[i]->SetCameraParameter(param,v) ;
	}
}