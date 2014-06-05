/*
 * farneBack.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: js
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/video/tracking.hpp>
#include"motion2color.h"

using namespace std;
using namespace cv;

int farneBack(string fileName) {
	VideoCapture capture(fileName);
	if (!capture.isOpened()) {
		cout << "open video file error!" << endl;
		return -1;
	}
	Mat prevGray, gray, flow, frame, motion2color;

	namedWindow("original", 1);
	namedWindow("farneBack", 1);

	while (true) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		imshow("original", frame);

		cvtColor(frame, gray, CV_BGR2GRAY);
		if (!prevGray.empty()) {
			calcOpticalFlowFarneback(prevGray, gray, flow, 0.5, 3, 15, 3, 5,
					1.2, 0);
			motionToColor(flow, motion2color);
			imshow("farneBack", motion2color);
		}

		if (waitKey(10) >= 0) {
			break;
		}
		std::swap(prevGray, gray);
	}
}
