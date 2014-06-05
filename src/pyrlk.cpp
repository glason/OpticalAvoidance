/*
 * pyrlk.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: js
 */

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/tracking.hpp>

#include"pyrlk.h"

using namespace std;
using namespace cv;

int pyrLK(string input) {
	VideoCapture cap(input);
	if (!cap.isOpened()) {
		cout << "open input video error!" << endl;
		return -1;
	}
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);

	const int MAX_COUNT = 500;

	namedWindow("pyrLK", 1);

	Mat gray, prevGray, image;
	vector<Point2f> points[2];

	for (;;) {
		Mat frame;
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0,
				0.04);
		cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);

		if (!points[0].empty()) {
			vector<uchar> status;
			vector<float> err;
			if (prevGray.empty())
				gray.copyTo(prevGray);
			calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status,
					err, winSize, 3, termcrit, 0, 0.001);
			size_t i, k;
			for (i = k = 0; i < points[1].size(); i++) {
				if (!status[i])
					continue;
				points[1][k++] = points[1][i];
				circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
			}
			points[1].resize(k);
		}
		imshow("pyrLK", image);

		if (waitKey(10) >= 0)
			break;
		std::swap(points[1], points[0]);
		cv::swap(prevGray, gray);
	}
	return 0;
}

