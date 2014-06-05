/*
 * motion2color.h
 *
 *  Created on: Jun 5, 2014
 *      Author: js
 */

#ifndef MOTION2COLOR_H_
#define MOTION2COLOR_H_

#include<opencv2/opencv.hpp>
using namespace cv;

void motionToColor(Mat flow, Mat &color);

#endif /* MOTION2COLOR_H_ */
