#ifndef BLOB_H_
#define BLOB_H_

#include <opencv2/core/core.hpp>

/*
 * Blob.h
 *  This class represents a two-colored hat blob. It stores blob position, rotation, velocity, and
 *  other data useful to the vision system.
 */

class Blob {
public:	
	/**
	 * Identifies a blob, it is computed based on the inner and outer colors.
	 */
    int id;
    /**
     * supposed to be the last capture time. relatively useless
     */
    double time;
    /**
     * Position on the x axis
     */
    double x;
    /**
     * Position on the y axis
     */
    double y;
    /**
     * Outer color of the blob.
     */
    int innerColor;
    /**
     * Inner color of the blob.
     */
    int outerColor;
    /**
     * Orientation of the blob, in radians in [0,2*pi]
     */
    double orientation;
    /**
     * Angular velocity of the bot in radians per second
     */
    double velocityRot;
    /**
     * Velocity along the x axis in pixels per second
     */
    double velocityx;
    /**
     * Velocity along the y axis in pixels per second
     */
    double velocityy;
	/**
	 * The predicted location of this blob in the next frame
	 */
	cv::Rect boundingBox;
};

#endif /* BLOB_H_ */
