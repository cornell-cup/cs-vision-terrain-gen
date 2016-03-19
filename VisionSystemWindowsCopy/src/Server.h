/*
 * Server.h
 *
 *  Created on: Nov 2, 2012
 *      Author: rh651-01user
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>

#include "VisionModule.h"
#include "Communication.h"
#include "BlobTracker.h"

/**
* This class is instantiated by the Communication class in a new thread. 
* It implements the interface defined in the Ice file to answer the queries from the base station.
* @see Communication
*/
class Server: public VisionModule::VisionInterface
{
private:
	BlobTracker* tracker;

public:
	/**
	* Just a test function, returns a random integer.
	*/
	virtual double ping(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, const Ice::Current &);
	/**
	* This function is called by the base station to retrieve the list of current objects.
	*/
	virtual VisionModule::VisionData getVision(const Ice::Current &);
	
	/**
	* Constructor.
	* @param blobTracker the instance of BlobTracker used by the vision system. We use this to retrieve the list of current objects.
	*/
	Server(BlobTracker* blobTracker);
};

#endif /* SERVER_H_ */
