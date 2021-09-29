#pragma once

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем работать с картинками (знаем про тип cv::Mat)

cv::Mat makeAllBlackPixelsBlue(cv::Mat image);

cv::Mat invertImageColors(cv::Mat image);

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat addUnicornsOnLargeBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat makeAllBlackPixelsToRandomColor(cv::Mat image);

cv::Mat makeAllClickedPixelsToRed(cv::Mat frame, std::vector<int> XClicks, std::vector<int> YClicks);

cv::Mat makeLargeCastleInsteadClickedColor(cv::Mat image, int lastX, int lastY, cv::Mat largeCastle);

cv::Mat dilate(cv::Mat mask, int r);

cv::Mat erode(cv::Mat mask, int r);

cv::Mat maskBackGround(cv::Mat image, int lastX, int lastY);