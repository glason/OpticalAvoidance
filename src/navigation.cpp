/*
 * navigation.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: js
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include"navigation.h"

using namespace cv;
using namespace std;

Vec2i foe(Mat flow) {
	int foeX = 0;
	float mX = 0;
	for (int i = 0; i < flow.rows; i++) {
		int tmp = 0;
		for (int j = 0; j < flow.cols; j++) {
			Vec2f point = flow.at<Vec2f>(i, j);
			tmp += point[0];
		}
		if (tmp < mX || mX == 0) {
			mX = tmp;
			foeX = i;
		}
	}

	int foeY = 0;
	float mY = 0;
	for (int j = 0; j < flow.cols; j++) {
		int tmp = 0;
		for (int i = 0; i < flow.rows; i++) {
			Vec2f point = flow.at<Vec2f>(i, j);
			tmp += point[1];
		}
		if (tmp < mY || mY == 0) {
			mY = tmp;
			foeY = j;
		}
	}

	return Vec2i(foeX, foeY);
}

Vec2i navigation(Mat flow) {
	Vec2f lt, rt, lb, rb;
	lt = Vec2f(0, 0);
	rt = Vec2f(0, 0);
	lb = Vec2f(0, 0);
	rb = Vec2f(0, 0);
	//left top
	for (int i = 0; i < flow.rows / 2; i++) {
		for (int j = 0; j < flow.cols / 2; j++) {
			Vec2f flow_at_point = flow.at<Vec2f>(i, j);
			lt[0] += flow_at_point[0];
			lt[1] += flow_at_point[1];
		}
	}
	//right top
	for (int i = flow.rows / 2; i < flow.rows; i++) {
		for (int j = 0; j < flow.cols / 2; j++) {
			Vec2f flow_at_point = flow.at<Vec2f>(i, j);
			rt[0] += flow_at_point[0];
			rt[1] += flow_at_point[1];
		}
	}
	//left bottom
	for (int i = 0; i < flow.rows / 2; i++) {
		for (int j = flow.cols / 2; j < flow.cols; j++) {
			Vec2f flow_at_point = flow.at<Vec2f>(i, j);
			lb[0] += flow_at_point[0];
			lb[1] += flow_at_point[1];
		}
	}
	//right bottom
	for (int i = flow.rows / 2; i < flow.rows; i++) {
		for (int j = flow.cols / 2; j < flow.cols; j++) {
			Vec2f flow_at_point = flow.at<Vec2f>(i, j);
			rb[0] += flow_at_point[0];
			rb[1] += flow_at_point[1];
		}
	}
	float avg_left = (lt[0] + lb[0]) / (flow.rows * flow.cols);
	float avg_right = (rt[0] + rb[0]) / (flow.rows * flow.cols);
	float avg_top = (lt[1] + rt[1]) / (flow.rows * flow.cols);
	float avg_bottom = (lb[1] + rb[1]) / (flow.rows * flow.cols);
	cout << "avg_left:" << fabs(avg_left) << endl;
	cout << "avg_right:" << fabs(avg_right) << endl;
	cout << "avg_top:" << fabs(avg_top) << endl;
	cout << "avg_bottom:" << fabs(avg_bottom) << endl;
	cout << "**********" << endl;
	int lor = fabs(avg_left) > fabs(avg_right) ? 1 : -1;
	int tob = fabs(avg_top) > fabs(avg_bottom) ? -1 : 1;
	return Vec2i(lor, tob);
}

