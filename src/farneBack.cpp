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
#include"navigation.h"

using namespace std;
using namespace cv;

int farneBack(string fileName) {
	VideoCapture capture(fileName);
//	VideoWriter writer;
	if (!capture.isOpened()) {
		cout << "open video file error!" << endl;
		return -1;
	}
//	writer.open("farneback.avi", CV_FOURCC('P', 'I', 'M', '1'),
//			capture.get(CV_CAP_PROP_FPS),
//			Size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH),
//					(int) capture.get(CV_CAP_PROP_FRAME_HEIGHT)), true);
//	if (!writer.isOpened()) {
//		cout << "output file open error!" << endl;
//		return -1;
//	}

	Mat prevGray, gray, flow, frame, motion2color, gauss;
	float y = 0, depth = 0;

	namedWindow("original", 1);
	namedWindow("farneBack", 1);

	while (true) {
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		imshow("original", frame);

		cvtColor(frame, gray, CV_BGR2GRAY);
		GaussianBlur(gray, gauss, Size(15, 15), 0, 0);

		if (!prevGray.empty()) {
			calcOpticalFlowFarneback(prevGray, gauss, flow, 0.5, 3, 15, 3, 5,
					1.2, 0);
			Vec2f flow_at_point = flow.at<Vec2f>(flow.rows / 2, flow.cols / 2);
			if (y != 0) {
				depth = (flow_at_point[1]) / ((flow_at_point[1] - y) * 100);
				depth = fabs(depth);
//				cout << "depth:" << depth << endl;
			}
			y = flow_at_point[1];

			Vec2i nav = foe(flow);
			cout << "foe:" << nav[0] << "," << nav[1] << endl;
			float px = frame.size().width * nav[1] / flow.cols;
			float py = frame.size().height * nav[0] / flow.rows;
			cout << px << "," << py << endl;
			line(frame, Point(px, py), Point(px, py), CV_RGB(255,0,0), 20);

			imshow("original", frame);
			motionToColor(flow, motion2color);
//			writer << motion2color;
			imshow("farneBack", motion2color);
		}

		if (waitKey(10) >= 0) {
			break;
		}
		std::swap(prevGray, gray);
	}
	return 1;
}
