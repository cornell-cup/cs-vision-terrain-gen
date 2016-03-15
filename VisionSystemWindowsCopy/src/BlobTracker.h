#ifndef BLOBTRACKER_H_
#define BLOBTRACKER_H_

#include <vector>

#include <boost/thread/mutex.hpp>

#include <opencv2/opencv.hpp>

#include "Blob.h"
#include "BlobResult.h"

#include "Vision.h"
#include "ModBotKalmanFilter.h"


/**
 * Filters, identifies, and tracks blobs.
 *
 * This class tracks the position and orientation of blobs over time. Given an
 * image in the "update" method, it filters blobs out of the image using the
 * cvBlobsLib. The blobs are filtered by size to get possible inner and outer
 * hat colors. Then hats are identified by finding which inner blobs exist
 * inside each outer blob. Finally, the hat blobs are used to update Kalman
 * filters associated with each hat.
 */
class BlobTracker {
public:
	/**
	 * Constructs a new BlobTracker.
	 *
	 * @param rgbFile The file to read rgb colors from
	 * @param initialTime The time of the first image capture
	 */
	BlobTracker(const char* rgbFile, double initialTime);

	/**
	 * Updates knowledge of blob positions by finding blobs in filteredImage.
	 *
	 * @param filteredImages An array of size NUM_SYSTEM_COLORS containing
	 * 	      images filtered for each color channel
	 * @param captureTime The time the filteredImages were captured, in seconds.
	 *        This time is relative to the "initialTime" the BlobTracker was
	 *        constructed with
	 */
	void update(const cv::Mat* filteredImages, std::vector<cv::Rect>& windows, double captureTime);

	/**
	 * Returns an image showing the blobs found in the merged image.
	 */
	const cv::Mat& getImage() const;

	/**
	 * Sets the size of the internal image used for drawing blobs.
	 *
	 * @param size The new size of the image
	 */
	void setImageSize(cv::Size size);

	/**
	 * @return the most recently found hats.
	 */
	const std::vector<Blob>& getCurrObjects() const;

	boost::mutex currObjectsLock;

	///@{
	/** Callbacks for the GUI to change blob areas.*/
	void setMinOuterBlobArea(int value);
	void setMaxOuterBlobArea(int value);
	void setMinInnerBlobArea(int value);
	void setMaxInnerBlobArea(int value);
	///@}

	///@{
	/** Variable for the GUI to change blob areas. */
	int minOuterBlobArea; // whole hat blob convex hull pixel area
	int maxOuterBlobArea; // whole blob convex hull pixel area
	int minInnerBlobArea; // hat spot blob convex hull pixel area
	int maxInnerBlobArea; // hat spot blob convex hull pixel area
	///@}

	/**
	 * BGR colors that correspond to each color channel. It is BGR rather than
	 * RBG because OpenCV reverses order.
	 */
    CvScalar bgrColors[NUM_SYSTEM_COLORS];

private:

	/**
	 * Filters potential inner and outer hat blobs from the image. The results
	 * are stored in the outerColorBlobResult and innerColorBlobResult member
	 * variables. This method is thread-safe, so images for different color
	 * channels can be filtered in parallel.
	 *
	 * @param channel The color channel index
	 * @param image The image in which blobs are located
	 */
	void filterBlobs(int i, const cv::Mat& image);

	/**
	 * Identifies hat blobs in a color channel. This method is thread-safe,
	 * so blobs from different channels can be identified in parallel.
	 *
	 * @param channel The color channel in which to identify blobs
	 */
	void identifyBlobs(int color_j, cv::Point offset);

	/**
	 * Attempts to find a "spot", or inner blob, inside the ellipse bounding an
	 * outer blob. Note that the results for this method are stored in the
	 * "color" and "spot" parameters.
	 *
	 * @param ellipse The bounding ellipse in which to check for inner blobs
	 * @param color The color of the found inner blob
	 * @param spot The bounding box of the inner blob
	 * @return True when inner blob has been found, false otherwise
	 */
	bool findSpot(CvBox2D& ellipse, int& color, CvBox2D& spot);

	/* Draws blobs found in roi to the displayImage */
	void drawBlobs(cv::Rect& roi);

	/**
	 * Update the ModBotKalmanFilters with the pending objects
	 * Fills currentObjects with filtered bots
	 */
	void kalmanFilterUpdate();

	/**
	 * Reads rgb colors from file.
	 *
	 * @returns true on success, false on failure
	 */
	bool readRgbColors(const char* fileName);

	/** Store potential outer blobs detected within each color channel. */
	CBlobResult outerColorBlobResult[NUM_SYSTEM_COLORS];
	/** Store potential inner blobs detected within each color channel */
	CBlobResult innerColorBlobResult[NUM_SYSTEM_COLORS];
	std::vector<Blob> colorObjects[NUM_SYSTEM_COLORS];
	
	/** GUI displayed image of filtered hat blobs and bounding rectangles */
    cv::Mat displayImage;
	
	/** Records the last capture time of the cameras (in seconds) */
    double lastCaptureTime;

	/** Records the time difference between cameras captures (in seconds) */
    double captureTimeDiff; //seconds

	
	/** Blobs ready to be updated in the Kalman filter */
    std::vector<Blob> pendingObjects;

	/** Hats from the current frame that are ready to be sent to base station */
	std::vector<Blob> currObjects;
	
	/** Map from color index to filter for position state */
    std::map<int, ModBotKalmanFilter> mbfkMap;
	
	// Boundaries for diameters; used in filtering
	int minOuterBlobDiam;
	int maxOuterBlobDiam;
	int minInnerBlobDiam;
	int maxInnerBlobDiam;
};

#endif /* BLOBTRACKER_H_ */
