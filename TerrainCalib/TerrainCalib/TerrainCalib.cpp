// TerrainCalib.cpp : blahblah
//

#include "stdafx.h"
#include "TerrainCalib.h"

using namespace cv;
using namespace std;


int main()
{
	Mat src, src1, gaus, hsv, imgthresh, processed;

	String file_name = "test3.jpg";

	src = imread(file_name, CV_LOAD_IMAGE_COLOR);
	src1 = imread(file_name, CV_LOAD_IMAGE_COLOR);
	//imshow("Image", src);

	cv::GaussianBlur(src, gaus, cv::Size(11, 11), 2, 2);
	cv::cvtColor(gaus, hsv, CV_BGR2HSV);
	//imshow("Gaussian", gaus);

	//open text file containing points and store in array
	vector <vector <string>> data;
	int row = 0;
	ifstream infile("points.txt");
	while (infile) {
		string s;
		if (!getline(infile, s)) break;
		istringstream ss(s);
		vector <string> record;
		row++;
		while (ss) {
			string s;
			if (!getline(ss, s, ',')) break;
			record.push_back(s);
		}
		data.push_back(record);
	}
	if (!infile.eof())
	{
		cerr << "Text file fail\n";
	}

	infile.close();
	//imshow("HSV", hsv);
	vector<cv::Mat> contours;
	//iterate through all rows of input points
	for (int i = 0; i < row; i++) {
		cv::Mat roi = hsv(cv::Rect(Point(stoi(data[i][0]), stoi(data[i][1])), Point(stoi(data[i][0]) + 100, stoi(data[i][1]) + 100)));
		imshow("roi" + to_string(i), roi);

		std::vector<cv::Mat> hsvPlanes;
		std::vector<cv::Mat> hsvPlanes2;
		cv::split(roi, hsvPlanes);
		cv::split(hsv, hsvPlanes2);

		cv::Scalar mean, stddev;
		cv::meanStdDev(hsvPlanes[0], mean, stddev);


		float minHue = mean[0] - (stddev[0] * 10);
		float maxHue = mean[0] + (stddev[0] * 10);

		cv::inRange(hsvPlanes2[0], cv::Scalar(minHue), cv::Scalar(maxHue), imgthresh);
		imshow("Threshold", imgthresh);

		erode(imgthresh, processed, 5);
		dilate(processed, processed, 20);
		imshow("Final" + to_string(i), processed);

		vector<vector<cv::Point>> contours; // Vector for storing contour
		vector<Vec4i> hierarchy;
		findContours(processed, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		Scalar color(255, 255, 0);  // color of the contour

		// sort contours largest to smallest
		std::sort(contours.begin(), contours.end(), compareContourAreas);
		std::reverse(contours.begin(), contours.end());

		const int num_contours = 2;
		if (contours.size() > num_contours) {
			contours.erase(contours.begin() + num_contours, contours.end());
		}

		write_to_obj_file("temp.obj", contours);
		
		std::cout << contours.size() << endl;

		// iterate through each contour.
		for (int i = 0; i < contours.size(); i++)
		{
			drawContours(src, contours, i, color, 5, 8);
		}
		namedWindow("Display window" + to_string(i), CV_WINDOW_AUTOSIZE);
		imshow("Display window" + to_string(i), src);
	}
	waitKey(0);
	return 0;
}

double get_width(vector<cv::Point> outside, vector<cv::Point> inside) {
	double min_dist = 10000000; //Arbitrary big number
	for (int o = 0; o < outside.size(); o++) {
		for (int i = 0; i < inside.size(); i++) {
			double dist = cv::norm(outside[o] - inside[i]);
			min_dist = dist < min_dist ? dist : min_dist;
		}
	}
	return min_dist;
}

// comparison function object
bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i < j);
}


/*
Writes the list of contours to the given file.
*/
void write_to_obj_file(string file_name, const vector<vector<cv::Point>> &contours) {
	//queue of vertex numbers representing start/end of a polygon. There is a polygon in between each two.
	queue<int> polygons;
	queue<Point> vertices;

	int point_num = 0;
	for (int i = 0; i < contours.size(); i++) {
		for (int j = 0; j < contours[i].size(); j++) {
			Point p = contours[i][j];
			vertices.push(p);
			point_num++;
		}
		polygons.push(point_num);
	}

	//Write polygon
	if (polygons.size() > 0) {
		ofstream file(file_name);

		//Write vertices
		while (vertices.size() != 0) {
			Point p = vertices.front();
			vertices.pop();
			file << "v " << p.x << " " << p.y << " 0 \n";
		}

		//Write polygons
		int prev_v = 1;
		while (polygons.size() != 0) {
			int lst_v = polygons.front();
			polygons.pop();

			file << "f ";
			for (int i = prev_v; i <= lst_v; i++) {
				file << i << " ";
			}
			file << "\n";

			prev_v = lst_v + 1;
		}
	}
}
