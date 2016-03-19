/*
 * View.cpp
 *
 *  Created on: Oct 20, 2012
 *	  Author: david
 */

#include <stdlib.h>
#include <math.h>

#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include "GUI.h"

using namespace std;

const string GUI::MERGED_WINDOW = "Merged Image";
const string GUI::FILTERED_WINDOW = "Filtered Image";

/**
 * Constructs a new GUI.
 *
 * @param cameraIds The ids of the cameras used by the system
 * @param ctrl The controller to be used by the GUI
 */
GUI::GUI(const vector<int>& cameraIds, Controller* ctrl) {
	controller = ctrl;

	// Create window names
	for (size_t i = 0; i < cameraIds.size(); i++) {
		stringstream ss;
		ss << "Camera " << i;
		windowNames.push_back(ss.str());
	}

	// By default, View not visible
	visible = false;
}

/**
 * Destroys the GUI's windows
 */
GUI::~GUI() {
	setVisible(false);
}

/**
 * Shows or hides the GUI
 *
 * @param b If b is true then show the GUI, otherwise hide it
 */
void GUI::setVisible(bool b) {
	if (b == visible) return;

	visible = b;

	// Create new windows or destroy existing
	if (visible) {
		BOOST_FOREACH(string& window, windowNames) {
			cv::namedWindow(window);
			cout << "Naming window: " << window << endl;
		}
		cv::namedWindow(MERGED_WINDOW);
		cv::namedWindow(FILTERED_WINDOW);
	} else {
		BOOST_FOREACH(string& window, windowNames) {
			cv::destroyWindow(window);
		}
		cv::destroyWindow(MERGED_WINDOW);
		cv::destroyWindow(FILTERED_WINDOW);
		// For some reason you have to put in a few delays to make the
		// GUI windows disappear
		for (int i = 0; i < 50; i++) {
			cv::waitKey(1);
		}
	}
}

/**
 * Returns the visibility state of the GUI.
 *
 * @return true if the GUI is currently visible, false otherwise
 */
bool GUI::isVisible() {
	return visible;
}

/**
 * Update the GUI with new images
 *
 * @param raw The raw camera imagese
 * @param merged The merged images
 * @param filtered The image
 */
void GUI::update(const cv::Mat* raw, const cv::Mat& merged,
		const cv::Mat& filtered) {
	if (visible) {
		for (unsigned int i = 0; i < windowNames.size(); i++) {
			cv::imshow(windowNames[i], raw[i]);
		}
		cv::imshow(MERGED_WINDOW, merged);
		cv::imshow(FILTERED_WINDOW, filtered);
	}
}

/**
 * Wait several milliseconds for a keystroke, and process it if it occurs.
 * Note that this method significantly slows down the vision system when
 * the GUI is visible. When the GUI is hidden, this method returns immediately.
 */
void GUI::processKey() {
	if (!visible)
		return;

	char key = (cv::waitKey(1) & 255);
	switch (key) {
	case 27:
		// Exit on escape key
		exit(0);
		break;
	case 'g':
		cout << "Removing GUI... ";
		setVisible(false);
		cout << "done." << endl;
		cout << "Enter Ctrl-C on command line to quit" << endl << endl;
		break;
	case 'o':
		controller->computeHomography();
		break;
	case 'r':
		cout << "Reading homography... ";
		controller->readHomography();
		cout << "done." << endl;
		break;
	case 'w':
		cout << "Writing homography... ";
		controller->writeHomography();
		cout << "done." << endl;
		break;
	case 'q':
		controller->showBlobSizeWindow();
		break;
	case 'l':
		if (controller->shouldLog()) {
			cout << "Turning off data logging... ";
		} else {
			cout << "Turning on data logging... ";
		}
		controller->toggleLogging();
		cout << "done." << endl;
		break;
	case '7' : 
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION1, 1);
		break;
	case '4' :
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION1, -1);
		break;
	case '8' :
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION2, 1);
		break;
	case '5' :
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION2, -1);
		break;
	case '9' :
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION3, 1);
		break;
	case '6' :
		controller->adjustLensCorrection(CLEYE_LENSCORRECTION3, -1);
		break;
	}
}
