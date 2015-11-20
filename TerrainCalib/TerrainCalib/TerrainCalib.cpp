// TerrainCalib.cpp : blahblah
//

#include "stdafx.h"
#include "TerrainCalib.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
	Mat src;
	src = imread("han.jpg", CV_LOAD_IMAGE_COLOR);
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	/*imshow("gray1", gray);*/
	GaussianBlur(src, src, Size(5, 5), 0, 0);
	//imshow("graygaus", gray);*/
	//threshold(gray, gray, 100, 255, THRESH_BINARY_INV); //Threshold the gray


	//open text file containing points and store in array
	ifstream infile;
	infile.open("points.txt");

	const size_t SIZE = 30;
	size_t i = 0;
	string line[SIZE];

	while (!infile.eof) {
		getline(infile, line[i]);
		++i;
	}

	infile.close();

	//iterate through all rows of input points
	for (int i = 0; i < sizeof(line[0]); i++) {
		Mat hsv;
		cvtColor(src, hsv, CV_BGR2HSV);
		Mat pointcvt = src(Rect(0, 0, 1, 1));
		Mat image2;
		cvtColor(pointcvt, image2, CV_BGR2HSV);

		upper = line[]
		lower =
		//threshold(gray, gray, 100, 255, THRESH_BINARY_INV)


	}
	
	imshow("gray", gray); int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	vector<cv::Mat> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;
	findContours(gray, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	Scalar color(255, 255, 0);  // color of the contour in the

	write_to_obj_file("temp.obj", contours);
	// iterate through each contour.
	for (int i = 0; i < contours.size(); i++)
	{
		drawContours(src, contours, i, color, 5, 8, hierarchy);
		////  Find the area of contour
		//double a = contourArea(contours[i], false);
		//if (a>largest_area){
		//	largest_area = a; cout << i << " area  " << a << endl;
		//	// Store the index of largest contour
		//	largest_contour_index = i;
		//	// Find the bounding rectangle for biggest contour
		//	bounding_rect = boundingRect(contours[i]);
		//}
	}

	//Draw the contour and rectangle

	//rectangle(src, bounding_rect, Scalar(0, 255, 0), 2, 8, 0);
	namedWindow("Display window", CV_WINDOW_AUTOSIZE);
	imshow("Display window", src);
	waitKey(0);
	return 0;
}

/*
Writes the list of contours to the given file.
*/
void write_to_obj_file(string file_name, const vector<cv::Mat> &contours){
	//queue of vertex numbers representing start/end of a polygon. There is a polygon in between each two.
	queue<int> polygons;
	queue<Point> vertices;

	int point_num = 0;
	for (int i = 0; i < contours.size(); i++){
		MatConstIterator_<Point> itr = contours[i].begin<Point>(), itr_end = contours[i].end<Point>();
		for (; itr != itr_end; itr++){
			Point p = *itr;
			vertices.push(p);
			point_num++;
		}
		polygons.push(point_num);
	}

	//Write polygon
	if (polygons.size() > 0){
		ofstream file(file_name);

		//Write vertices
		while (vertices.size() != 0){
			Point p = vertices.front();
			vertices.pop();
			file << "v " << p.x << " " << p.y << "\n";
		}

		//Write polygons
		int prev_v = 1;
		while (polygons.size() != 0){
			int lst_v = polygons.front();
			polygons.pop();
			
			file << "f ";
			for (int i = prev_v; i <= lst_v; i++){
				file << i << " ";
			}
			file << "\n";

			prev_v = lst_v + 1;
		}
	}
}
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//using namespace cv;
//using namespace std;
//
//Mat src; Mat src_gray;
//int thresh = 100;
//int max_thresh = 255;
//RNG rng(12345);
//
///// Function header
//void thresh_callback(int, void*);
//
///** @function main */
//int main(int argc, char** argv)
//{
//	/// Load source image and convert it to gray
//	src = imread("cute.jpg", 1);
//
//	/// Convert image to gray and blur it
//	cvtColor(src, src_gray, CV_BGR2GRAY);
//	blur(src_gray, src_gray, Size(3, 3));
//
//	/// Create Window
//	char* source_window = "Source";
//	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
//	imshow(source_window, src);
//
//	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
//	thresh_callback(0, 0);
//
//	waitKey(0);
//	return(0);
//}
//
///** @function thresh_callback */
//void thresh_callback(int, void*)
//{
//	Mat canny_output;
//	vector<vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//
//	/// Detect edges using canny
//	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
//	/// Find contours
//	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//	/// Get the moments
//	vector<Moments> mu(contours.size());
//	for (int i = 0; i < contours.size(); i++)
//	{
//		mu[i] = moments(contours[i], false);
//	}
//
//	///  Get the mass centers:
//	vector<Point2f> mc(contours.size());
//	for (int i = 0; i < contours.size(); i++)
//	{
//		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
//	}
//
//	/// Draw contours
//	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
//	for (int i = 0; i< contours.size(); i++)
//	{
//		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
//		circle(drawing, mc[i], 4, color, -1, 8, 0);
//	}
//
//	/// Show in a window
//	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
//	imshow("Contours", drawing);
//
//	/// Calculate the area with the moments 00 and compare with the result of the OpenCV function
//	printf("\t Info: Area and Contour Length \n");
//	for (int i = 0; i< contours.size(); i++)
//	{
//		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
//		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
//		circle(drawing, mc[i], 4, color, -1, 8, 0);
//	}
//}

//#include "opencv2/opencv.hpp"
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//
//	// Read image
//	Mat im = imread("cute.jpg", IMREAD_GRAYSCALE);
//
//	// Setup SimpleBlobDetector parameters.
//	SimpleBlobDetector::Params params;
//
//	// Change thresholds
//	params.minThreshold = 10;
//	params.maxThreshold = 200;
//
//	// Filter by Area.
//	params.filterByArea = true;
//	params.minArea = 1500;
//
//	// Filter by Circularity
//	params.filterByCircularity = true;
//	params.minCircularity = 0.1;
//
//	// Filter by Convexity
//	params.filterByConvexity = true;
//	params.minConvexity = 0.87;
//
//	// Filter by Inertia
//	params.filterByInertia = true;
//	params.minInertiaRatio = 0.01;
//
//
//	// Storage for blobs
//	vector<KeyPoint> keypoints;
//
//
//	// Set up detector with params
//	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
//
//	// Detect blobs
//	detector->detect(im, keypoints);
//
//	// Draw detected blobs as red circles.
//	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
//	// the size of the circle corresponds to the size of blob
//
//	Mat im_with_keypoints;
//	drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//
//	// Show blobs
//	imshow("keypoints", im_with_keypoints);
//	waitKey(0);
//
//}