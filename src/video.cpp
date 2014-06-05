/*
 * video.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: js
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"video.h"

using namespace cv;
using namespace std;

int codec = CV_FOURCC('P', 'I', 'M', '1');
int fps = 25;

int record(string fileName) {
	VideoCapture capture;
	VideoWriter writer;
	Mat frame;
	capture.open(0);
	if (!capture.isOpened()) {
		cout << "open camera error!" << endl;
		return -1;
	}
	writer.open(fileName, codec, fps,
			Size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH),
					(int) capture.get(CV_CAP_PROP_FRAME_HEIGHT)), true);
	if (!writer.isOpened()) {
		cout << "output file open error!" << endl;
		return -1;
	}
	while (true) {
		capture >> frame;
		imshow("recording...", frame);
		writer << frame;
		if (waitKey(15) >= 0) {
			break;
		}
	}
	return 0;
}

