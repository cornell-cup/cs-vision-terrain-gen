#ifndef TIMER_H_
#define TIMER_H_

/**
 * Timer.h
 * Author: David Felty (djf242)
 *
 * The purpose of this class is to provide an accurate timer that can be used
 * to profile functions at runtime. The timer used is not thread-dependent, so
 * it should work even in concurrent situations. (Just make sure threads don't
 * share the same timer object.)
 *
 * The entire class exists in the header so that its functions can be inlined.
 * This speeds up timer functions so they don't slow down timing and skew results.
 */

#include <opencv2\opencv.hpp>

class Timer {
public:

	/** Create a new timer */
	Timer() {
		clearAverage();
	}

	/** Begin timing */
	inline void start() {
		// System-wide increasing-only clock; not thread dependent
		startTime = cv::getTickCount();
	}

	/** Stop timing */
	inline void stop() {
		timeDiff = cv::getTickCount() - startTime;
		totalTime += timeDiff;
		numTimings++;
	}

	/** Returns the most recent timing (in seconds) */
	inline double getLast() {
		return toSeconds(timeDiff);
	}

	/** Returns the average of all the timing since the last time clearAverage() was called */
	inline double getAverage() {
		if (numTimings == 0) return 0;
		return toSeconds(totalTime) / static_cast<double>(numTimings);
	}

	/** Returns the start time of the most recent timing */
	inline double getStart() {
		return toSeconds(startTime);
	}

	/** Returns the end time of the most recent timing */
	inline double getEnd() {
		return getStart() + getLast();
	}

	/** Resets the average for this timer */
	inline void clearAverage() {
		totalTime = 0;
		numTimings = 0;
	}

private:
	int64 startTime;
	int64 timeDiff;
	int64 totalTime;
	int numTimings;

	inline static double toSeconds(int64 tickCount) {
		return ((double) tickCount) / cv::getTickFrequency();
	}

};

#endif /* TIMER_H */
