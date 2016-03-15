#ifndef CLIENT_H_
#define CLIENT_H_

#include "VisionModule.h"
#include "BlobTracker.h"


VisionModule::VisionData getVision(BlobTracker* tracker);

class Client {
public:

	Client();
	virtual ~Client();
};
#endif

