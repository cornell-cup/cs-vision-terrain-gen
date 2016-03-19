#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <boost/function.hpp>

#include "ImageMerging.h"
#include "ImageFiltering.h"
#include "BlobTracker.h"
#include "CLEyeHandler.h"


class Controller {
public:

	/**
	 * Constructs a new Controller object.
	 *
	 * @param c The CameraHandler object
	 * @param m The ImageMerging object
	 * @param f The ImageMerging object
	 * @param b The BlobTracker object
	 */
	Controller(CLEyeHandler* c, ImageMerging* m, ImageFiltering* f, BlobTracker* b);
	
	/**
	 * Computes a homography for the camera configuration using the
	 * checkerboard method.
	 *
	 * Triggered by the 'o' key, which stands for "Offset calculation".
	 */
	void computeHomography();
	
	/**
	 * Reads a homography from the HOMOGRAPHY_FILE defined in Vision.h.
	 *
	 * Triggered by the 'r' key.
	 */
	void readHomography();
	
	/**
	 * Writes the current homography to the HOMOGRAPHY_FILE defined in Vision.h
	 *
	 * Triggered by the 'w' key.
	 */
	void writeHomography();
	
	/**
	 * Shows a settings window for modifying blob size thresholds.
	 *
	 * Triggered by the 'q' key.
	 */
	void showBlobSizeWindow();	

	/**
	 * Toggles data logging
	 *
	 * Triggered by the 'l' key.
	 */
	void toggleLogging();

	/**
	 * Indicates to Vision.cpp whether or not data logging should occur
	 * @return whether or not data logging should occur
	 */
	bool shouldLog();


	/**
	 * Adjusts camera lens correction variables by a specified offset. 
	 *
	 * The following keys adjust the lens correction variables as follows:
	 * '7' / '4  : Increase / Decrease k1 by 1
	 * '8' / '5' : Increase / Decrease k2 by 1
	 * '9' / '6' : Increase / Decrease k3 by 1
	 */
	void adjustLensCorrection(CLEyeCameraParameter p, int change);
	
	/** Type used for callbacks that modify the blob area thresholds */
	typedef boost::function<void (int)> AreaCallback;

private:
	/** \name Model variables */
	///@{
	CLEyeHandler* cameras;
	ImageMerging* merger;
	ImageFiltering* filter;
	BlobTracker* tracker;
	///@}
	
	/** Camera correction variables */
	int k1, k2, k3;

	/* Name given to the window for adjusting blob sizes */
	static const string BLOB_SIZE_WINDOW;

	// Blob Area pointers, used to set position of trackbars.
	// These point to member variables of the BlobTracker object.
	int* minOuterBlobArea;
	int* maxOuterBlobArea;
	int* minInnerBlobArea;
	int* maxInnerBlobArea;
	
	// Boolean to indicate whethter or not we should log data
	bool logEnabled;

	// Functions used to modify blob area thresholds
	AreaCallback setMinOuterBlobArea;
	AreaCallback setMaxOuterBlobArea;
	AreaCallback setMinInnerBlobArea;
	AreaCallback setMaxInnerBlobArea;
};

#endif /* CONTROLLER_H_ */
