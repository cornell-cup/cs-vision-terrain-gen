#include "VisionModule.h"
#include "BlobTracker.h"
#include "Client.h"

using namespace std;

/** Packages current vision data into a Blob array to send to the 
 * base station 
 */
VisionModule::VisionData getVision(BlobTracker* tracker) {
	VisionModule::VisionData convertedData;
	//cout << "Size: " << tracker->getCurrObjects().size();
	tracker->currObjectsLock.lock();
	const std::vector<Blob>& currObjects = tracker->getCurrObjects();
	for (unsigned int i = 0; i < currObjects.size(); i++) {
		VisionModule::Blob ndata;
		ndata.x = currObjects[i].x / PIXELS_PER_METER;
		ndata.y = currObjects[i].y / PIXELS_PER_METER; 
		ndata.isProjectile = 0;

		ndata.color1.redValue = tracker->bgrColors[currObjects[i].innerColor].val[2];
		ndata.color1.greenValue = tracker->bgrColors[currObjects[i].innerColor].val[1];
		ndata.color1.blueValue = tracker->bgrColors[currObjects[i].innerColor].val[0];

		ndata.color2.redValue = tracker->bgrColors[currObjects[i].outerColor].val[2];
		ndata.color2.greenValue = tracker->bgrColors[currObjects[i].outerColor].val[1];
		ndata.color2.blueValue = tracker->bgrColors[currObjects[i].outerColor].val[0];

		ndata.orientation = currObjects[i].orientation;
		ndata.velocityx = currObjects[i].velocityx / PIXELS_PER_METER;
		ndata.velocityy = currObjects[i].velocityy / PIXELS_PER_METER;
		ndata.velocityRot = currObjects[i].velocityRot;
		ndata.botID = currObjects[i].id;
		//cout << "Velocity x: " << ndata.velocityx;
		//ndata.time = data[i].time;
		ndata.time = (double) time(NULL) * 1000;
		convertedData.push_back(ndata);
	}
	//cout << "Size: " << tracker->getCurrObjects().size();
	tracker->currObjectsLock.unlock();

	return convertedData;
}

Client::Client(){}

Client::~Client(){}