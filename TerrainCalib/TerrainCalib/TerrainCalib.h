#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp""
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace cv;
using namespace std;

int main();

void write_to_obj_file(string file_name, const vector<cv::Mat> &contours);