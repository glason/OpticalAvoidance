/*
 * navigation.h
 *
 *  Created on: Jun 12, 2014
 *      Author: js
 */

#ifndef NAVIGATION_H_
#define NAVIGATION_H_
#include<opencv2/opencv.hpp>
using namespace cv;

Vec2i foe(Mat flow);
Vec2i navigation(Mat flow);

#endif /* NAVIGATION_H_ */
