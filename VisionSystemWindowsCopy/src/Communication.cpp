/*
 * Communication.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: rh651-01user
 */

#include "Communication.h"
#include "VisionModule.h"

/**
* Actually create the server for the base station to poll.
*/
void* createServer(void* param) {
	BlobTracker* blobTracker = (BlobTracker*) param;
	Ice::CommunicatorPtr communicator;
	try {
		communicator = Ice::initialize();
		Ice::ObjectAdapterPtr adpt =
				communicator->createObjectAdapterWithEndpoints("Ping",
						"tcp -p 10003");
		adpt->add(new Server(blobTracker),
				communicator->stringToIdentity("Ping"));
		adpt->activate();
		std::cout << "PING SERVER STARTED!!!!" << std::endl;
		communicator->waitForShutdown();
		communicator->destroy();
	} catch (const Ice::Exception& ex) {
		std::cerr << ex << std::endl;
	} 
	return 0;
}


VisionModule::BaseInterfacePrx createClient(){
	try
	{
		Ice::CommunicatorPtr communicator = Ice::initialize();

		Ice::ObjectPrx prx;
		prx = communicator->stringToProxy("Ping:tcp -h 192.168.1.16 -p 10009");
		VisionModule::BaseInterfacePrx base = VisionModule::BaseInterfacePrx::checkedCast(prx);
		std::cout << "Connection successful" << std::endl;
		return base;
		
		communicator->destroy();
	}
	catch (...)
	{
		std::cout << "Cannot connect to base" << std::endl;
	}
	return 0;
}


Communication::Communication(BlobTracker* blobTracker) {
	try {
		boost::thread th(createServer, (void*) blobTracker);
	} catch (const Ice::Exception& ex) {
		std::cerr << ex << std::endl;
	}
}

Communication::~Communication() {
	// TODO Auto-generated destructor stub
}

