/*
 * main.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: js
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<stdio.h>
#include<math.h>
#include"video.h"
#include"pyrlk.h"
#include"farneBack.h"

using namespace cv;
using namespace std;

int main() {
//	farneBack("flight.mp4");
//	record("record.avi");
	farneBack("iphone.mov");
	return 0;
}

