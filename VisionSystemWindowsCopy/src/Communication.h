/*
 * Communication.h
 *
 *  Created on: Nov 2, 2012
 *      Author: rh651-01user
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include <Ice/Ice.h>
#include <iostream>

#include <vector>
#include <exception>

#include <boost\thread.hpp>

#include "Server.h"
#include "VisionModule.h"
#include "BlobTracker.h"


VisionModule::BaseInterfacePrx createClient();
/**
* This class handles all communications with the base station.
*/
class Communication {
public:
	
	/**
	* Start the communication server in a new thread.
	*/
	Communication(BlobTracker* blobTracker);
	virtual ~Communication();
};

#endif /* COMMUNICATION_H_ */
