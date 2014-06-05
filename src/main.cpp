/*
 * main.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: js
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"video.h"
#include"pyrlk.h"
#include"farneBack.h"

using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	farneBack("test.avi");
	return 0;
}

