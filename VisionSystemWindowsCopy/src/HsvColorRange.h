#ifndef HSV_THRESH_COLOR_H_
#define HSV_THRESH_COLOR_H_

#include <stdio.h>
#include <string>

/**
* This structure is used to store information about a color we want to detect. 
* It basically stores the ranges of acceptable hue, saturation and value for this color.
*/
struct HsvColorRange {
	std::string name;
	struct {
		int lo;
		int hi;
	} h, s, v;
    
	/** Constructor, specify the name and ranges for hue, saturation and value */
	HsvColorRange(const std::string& name, int hLo, int hHi, int sLo, int sHi, int vLo, int vHi) {
		this->name = name;
		h.lo = hLo;
		h.hi = hHi;
		s.lo = sLo;
		s.hi = sHi;
		v.lo = vLo;
		v.hi = vHi;
	}
	
	/** Default constructor with a zero hue and standard saturation and value in  [50, 255], name is "a color"*/
	HsvColorRange() {
		this->name = "a color";
		h.lo = 0;
		h.hi = 0;
		s.lo = 40;
		s.hi = 255;
		v.lo = 40;
		v.hi = 255;
	}
};

#endif
