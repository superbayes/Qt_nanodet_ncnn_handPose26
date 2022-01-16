#pragma once
#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "NanoDetPLUS1.h"
using namespace std;

int main(void) 
{
	cv::Mat image = cv::imread("./img/hand26_03.jpg",-1);
	
	NanoDetPLUS1 detector = NanoDetPLUS1(
		"./model/nanodet-plus-m-1.5x_416_hand26_20220116.param", 
		"./model/nanodet-plus-m-1.5x_416_hand26_20220116.bin");
	cv::Mat dst;
	if (image.empty())
	{
		printf("image is empty!!!");
		return -1;
	}
	auto results = detector.detect(image, 0.7, 0.5);
	detector.draw(image, results);
	printf("============\n");
}