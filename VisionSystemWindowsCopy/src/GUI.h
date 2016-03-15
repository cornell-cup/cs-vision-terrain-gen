#ifndef GUI_H_
#define GUI_H_
/*
 * GUI.h
 *
 *  Created on: Oct 20, 2012
 *      Author: djf242
 */

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "Controller.h"

/**
 * Graphical interface for the Vision system.
 *
 * The GUI is useful for two main things:
 * 	 1. Visualization
 * 	 2. User input
 * The GUI puts several windows on the screen. The first are the camera feeds,
 * which show the video being streamed from the cameras. There can be several
 * of these. There is also a window for a merged image window, which by default
 * shows only camera 0. But when the program is commanded to merge the images,
 * this window will show the result of merging. Finally, there is a window that
 * displays the blobs that have been found in the merged image. The hat blobs
 * are drawn with velocity and orientation indicators.
 *
 * Note that the GUI is not thread-safe. That is, it cannot be run concurrently
 * with many of the other main methods of the vision system, as it modifies
 * crucial variables that are used to control image processing.
 *
 * The GUI carries out its actions through the Controller class. This Separates
 * the GUI from the state of the rest of the program.
 * @see Controller
 */
class GUI {
public:
	/**
	 * Constructs a new GUI.
	 *
	 * @param cameraIds The ids of the cameras used by the system
	 * @param ctrl The controller to be used by the GUI
	 */
	GUI(const std::vector<int>& cameraIds, Controller* ctrl);

	/**
	 * Destroys the GUI's windows
	 */
	~GUI();

	/**
	 * Shows or hides the GUI
	 *
	 * @param b If b is true then show the GUI, otherwise hide it
	 */
	void setVisible(bool b);

	/**
	 * Returns the visibility state of the GUI.
	 *
	 * @return true if the GUI is currently visible, false otherwise
	 */
	bool isVisible();

	/**
	 * Update the GUI with new images
	 *
	 * @param raw The raw camera imagese
	 * @param merged The merged images
	 * @param filtered The image
	 */
	void update(const cv::Mat* raw, const cv::Mat& merged, const cv::Mat& filtered);

	/**
	 * Wait several milliseconds for a keystroke, and process it if it occurs.
	 * Note that this method significantly slows down the vision system when
	 * the GUI is visible. When the GUI is hidden, this method returns immediately.
	 */
	void processKey();

	/**
	 * Shows the blob size window, which allows adjustment of the blob
	 * area boundaries.
	 */
	void showBlobSizeWindow();

	/**
	 * Shows the color settings window, which can be used to adjust hsv color
	 * threshold settings.
	 */
	void showColorSettingsWindow(unsigned int color);

private:

	/** True when GUI is visible */
	bool visible;

	/** Controller object used to carry out actions */
	Controller* controller;

	/** Names of raw camera image windows */
	std::vector<std::string> windowNames;

	// Names of various other windows
	static const std::string MERGED_WINDOW;
	static const std::string FILTERED_WINDOW;
};

#endif /* VIEW_H_ */