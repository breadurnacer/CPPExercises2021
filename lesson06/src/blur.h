#pragma once

#include <opencv2/highgui.hpp>

cv::Mat blur(cv::Mat img, double sigma);

double gauss(int x, int y, double sigma);