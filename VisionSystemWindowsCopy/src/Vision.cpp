//============================================================================
// Name        : Vision.cpp
// Author      : Cornell Cup presented by Intel
// Version     :
// Copyright   : 
// Description : Project's entry point
//============================================================================

#include <iostream>

#include <boost/foreach.hpp>

#include "Vision.h"
#include "ImageFiltering.h"
#include "Blob.h"
#include "ImageMerging.h"
#include "Communication.h"
#include "ImageFiltering.h"
#include "GUI.h"
#include "Controller.h"
#include "Timer.h"
#include "PipelineManager.h"
#include <fstream>;
#include "Client.h"

using namespace std;

int main() {
	//=========================================================================
	// INITIAL SETUP
	//=========================================================================
	// Assign camera ids, number of cameras is defined in Vision.h
	vector<int> camId(NUM_CAMERAS); 
	camId[0] = 0;
	camId[1] = 1;
	camId[2] = 2;
	camId[3] = 3;

	// Get an initial time (needed by BlobTracker)
	Timer tmp;
	tmp.start();
	double initialTime = tmp.getStart();

	//=========================================================================
	// INITIALIZE IMPORTANT CLASSES
	//=========================================================================
	CLEyeHandler cameras(camId);							// Handles concurrent capturing of camera images
	ImageMerging merger;									// Merges multiple camera images into a single image
	ImageFiltering filter(HSV_FILE);						// Handles filtering of camera images
	BlobTracker tracker(RGB_FILE, initialTime);				// Tracks blob positions
	Controller ctrl(&cameras, &merger, &filter, &tracker);	// Processes commands coming in from the GUI
	//Communication comm(&tracker);							// Sends blob position data to ModBot Control GUI
	GUI gui(camId, &ctrl);									// Allows users to interact with vision system
	
	VisionModule::BaseInterfacePrx baseStation;

	try {
		baseStation = createClient();
	}
	catch (...){}


	

	//=========================================================================
	// FINAL SETUP
	//=========================================================================
	// Show GUI windows
	gui.setVisible(true);
	
	// Need to give the merger an initial image so it can be used for determining windows
	ImagePointer* ptr = cameras.pipeline.readRequest();
	merger.update(*ptr, cv::Rect(cv::Size(0, 0), ptr->images[0].size()));
	cameras.pipeline.readRelease();

	// Initialize a timer to keep track of image request time
	Timer imageRequestTime;

	// Initialize a text file for data logging
	ofstream outFile(LOG_FILE, std::ofstream::out | std::ofstream::trunc);
	if (outFile.is_open()) {  
		outFile <<  "ID\t" << "XPOS(m)\t" << "YPOS(m)\t" << "ROT(rad)\t" << "XVEL(m/s)\t" << "YVEL(m/s)\t" << "ROTVEL(rad/s)\t" << "TIME(s)" << endl;
	}


	//=========================================================================
	// LETS DO THIS THANG (RUN MAIN VISION LOOP)
	//=========================================================================
	while (true) {
		// Determine windows to look at
		vector<cv::Rect> windows;
		const std::vector<Blob>& blobs = tracker.getCurrObjects();
		cv::Rect fullImage(cv::Size(0,0), merger.getMergedImage().size());
		if (blobs.size() < NUM_BLOBS) {
			windows.push_back(fullImage);
		} else {
			BOOST_FOREACH(const Blob& b, blobs) {
				windows.push_back(b.boundingBox & fullImage);
			}
		}

		// Fetch images from multiple cameras
		imageRequestTime.start();
		ImagePointer* images = cameras.pipeline.readRequest();
		imageRequestTime.stop();
		
		// Merge multiple camera images into a single image
		BOOST_FOREACH(cv::Rect& w, windows) {
			merger.update(*images, w);
		}
		const cv::Mat& merged = merger.getMergedImage();

		// Filter merged image to only include the colors we are interested in
		BOOST_FOREACH(cv::Rect& w, windows) {
			filter.filter(merged, w);
		}

		// Find blobs in filtered image
		tracker.update(filter.getFilteredImages(), windows, imageRequestTime.getStart());
		
		// Send blobs to base station
		try{
			baseStation->update(getVision(&tracker));
		} catch (...){}

		// Finished processing blobs, so stop latency timer
		ptr->timer.stop();

		
		

		// Update GUI windows
		if (gui.isVisible()) {
			// Draw minor guide lines on the merged image (spacing should be 0.2m)
			cv::Mat displayMerged=cv::Mat(merged);
			for(int i=0;i<30;i++) {
				cv::line(displayMerged, cv::Point(i*PIXELS_PER_METER/5,0), cv::Point(i*PIXELS_PER_METER/5,displayMerged.size[0]), cv::Scalar(50,50,50));
				cv::line(displayMerged, cv::Point(0,i*PIXELS_PER_METER/5), cv::Point(displayMerged.size[1],i*PIXELS_PER_METER/5), cv::Scalar(50,50,50));
			}
			// Draw major guide lines on the merged image (spacing should be 1m)
			for(int i=0;i<6;i++) {
				cv::line(displayMerged, cv::Point(i*PIXELS_PER_METER,0), cv::Point(i*PIXELS_PER_METER,displayMerged.size[0]), cv::Scalar(180,180,180));
				cv::line(displayMerged, cv::Point(0,i*PIXELS_PER_METER), cv::Point(displayMerged.size[1],i*PIXELS_PER_METER), cv::Scalar(180,180,180));
			}
			gui.update(images->images, displayMerged, tracker.getImage());
			// Release before processing keys, so we can do calibration
			cameras.pipeline.readRelease();
			gui.processKey();
		} else {
			//Release: done doing stuff with images
			cameras.pipeline.readRelease();
		}

		// Output blob positions and log positions to data file if enabled
		BOOST_FOREACH(const Blob& b, tracker.getCurrObjects()) {
			// Convert from pixel coordinates to meters (conversion factor is defined in Vision.h
			double x = b.x / PIXELS_PER_METER;
			double y = b.y / PIXELS_PER_METER;
			double vx = b.velocityx / PIXELS_PER_METER;
			double vy = b.velocityy / PIXELS_PER_METER;

			printf("[t=%f] Blob {id:%d, x:%f, y:%f, o:%f}\n", b.time-initialTime, b.id, x, y, b.orientation);
			
			if (ctrl.shouldLog()) {
				ofstream outFile(LOG_FILE, std::ofstream::out | std::ofstream::app);
				if (outFile.is_open()) {
					outFile <<  b.id << "\t" << x << "\t" << y << "\t" << b.orientation << "\t" << vx << "\t" << vy << "\t" << b.velocityRot << "\t" << b.time-initialTime << endl;
				} else {
					cerr << "ERROR : Unable to open file, check that it is not currently open elsewhere" << endl;
				}
			}
		}
	}
}