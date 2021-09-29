#include "helper_functions.h"
#include <ctime>
#include <libutils/rasserts.h>
#include <cstdlib>
#include <iostream>


cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
    // TODO реализуйте функцию которая каждый черный пиксель картинки сделает синим

    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j){
    cv::Vec3b color = image.at<cv::Vec3b>(j, i);
    unsigned char blue = color[0];
    unsigned char green = color[1];
    unsigned char red = color[2];
    if(blue == 0 && green == 0 && red == 0){
        blue = 255;
        green = 0;
        red = 0;
    }
    image.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, green, red);}}

    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)

    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j){
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];

                blue = 255 - blue;
                green = 255 - green;
                red = 255 - red;

            image.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, green, red);}}

    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится

    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
    rassert(object.cols == background.cols, "cols should be ==");
    rassert(object.rows == background.rows, "rows should be ==");

    for(int i = 0; i < object.cols; ++i){
        for(int j = 0; j < object.rows; ++j){
            cv::Vec3b color = object.at<cv::Vec3b>(j, i);
            cv::Vec3b backcolor = background.at<cv::Vec3b>(j,i);

            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];

            unsigned char blueback = backcolor[0];
            unsigned char greenback = backcolor[1];
            unsigned char redback = backcolor[2];
            if(blue == 0 && green == 0 && red == 0){
                object.at<cv::Vec3b>(j, i) = cv::Vec3b(blueback, greenback, redback);
            }
        }}
    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground) {
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)
    rassert(largeBackground.cols > object.cols && largeBackground.rows > object.rows, "background is not enough big.");
    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы
    int y0 = (largeBackground.rows - object.rows)/2;
    int x0 = (largeBackground.cols - object.cols)/2;

    for(int i = 0; i < object.cols; ++i){
        for(int j = 0; j < object.rows; ++j){
            cv::Vec3b color = object.at<cv::Vec3b>(j, i);
            //cv::Vec3b backcolor = largeBackground.at<cv::Vec3b>(y0+ j,x0+ i);
            if(color[0] != 0 || color[1] !=0 || color[2] != 0 ){
                largeBackground.at<cv::Vec3b>(y0+ j,x0+ i) = color;
            }
        }
    }

    return largeBackground;
}

cv::Mat addUnicornsOnLargeBackground(cv::Mat object, cv::Mat largeBackground) {

    rassert(largeBackground.cols > object.cols && largeBackground.rows > object.rows, "background is not enough big.");

    std::srand((unsigned)std::time(0));
    int N = std::rand() % 101;
for(int f = 0; f < N; ++f){
    int y0 = std::rand() % (largeBackground.rows + 1 - object.rows);
    int x0 = std::rand() % (largeBackground.cols + 1 - object.cols);

    for (int i = 0; i < object.cols; ++i) {
        for (int j = 0; j < object.rows; ++j) {
            cv::Vec3b color = object.at<cv::Vec3b>(j, i);
            //cv::Vec3b backcolor = largeBackground.at<cv::Vec3b>(y0+ j,x0+ i);
            if (color[0] != 0 || color[1] != 0 || color[2] != 0) {
                largeBackground.at<cv::Vec3b>(y0 + j, x0 + i) = color;
            }
        }
    }
}

    return largeBackground;
}

cv::Mat makeAllBlackPixelsToRandomColor(cv::Mat image){
    std::srand((unsigned)std::time(0));
    int randBlue = std::rand()%256;
    int randGreen = std::rand()%256;
    int randRed = std::rand()%256;
    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j){
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            if(blue == 0 && green == 0 && red == 0){
                blue = randBlue;
                green = randGreen;
                red = randRed;
            }
            image.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, green, red);}}

    return image;
}

cv::Mat makeAllClickedPixelsToRed(cv::Mat frame, std::vector<int> XClicks, std::vector<int> YClicks){
    for(int i = 0; i < XClicks.size(); ++i){
        frame.at<cv::Vec3b>(YClicks[i], XClicks[i]) = cv::Vec3b(0,0,255);
    }
    return frame;
}

cv::Mat makeLargeCastleInsteadClickedColor(cv::Mat image, int lastX, int lastY, cv::Mat largeCastle){
    cv::Vec3b colorBG = image.at<cv::Vec3b>(lastY, lastX);
    unsigned char blueBG = colorBG[0];
    unsigned char greenBG = colorBG[1];
    unsigned char redBG = colorBG[2];


    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j) {
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            cv::Vec3b colorCastle = largeCastle.at<cv::Vec3b>(j,i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            if (abs(blue - blueBG) <= 5 && abs(green - greenBG) <= 5 && abs(red - redBG) <= 5) {
                blue = colorCastle[0];
                green = colorCastle[1];
                red = colorCastle[2];
            }
             image.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, green, red);}}
    return image;
}


cv::Mat maskBackGround(cv::Mat image, int lastX, int lastY){
    cv::Mat resMask(image.rows, image.cols, CV_8UC1, Scalar((unsigned char)0));

    cv::Vec3b colorBG = image.at<cv::Vec3b>(lastY, lastX);
    unsigned char blueBG = colorBG[0];
    unsigned char greenBG = colorBG[1];
    unsigned char redBG = colorBG[2];


    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j) {
            cv::Vec3b color = image.at<cv::Vec3b>(j, i);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            if (abs(blue - blueBG) <= 5 && abs(green - greenBG) <= 5 && abs(red - redBG) <= 5) {
                resMask.at<unsigned char>(ny,nx) = 1;
            }
            image.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, green, red);}}
    return image;
}



cv::Mat dilate(cv::Mat mask, int r){
    cv::Mat resMask = mask.clone();

    for(int x = 0; x < mask.cols; ++x){
        for(int y = 0; y < mask.rows; ++y){
            if(mask.at<unsigned char>(y,x) == 1){
            for(int dx = -r; dx < r; ++r){
                for(int dy = -r; dy < r; ++r){
                    int nx = x + dx;
                    int ny = y + dy;
                    if(!(nx<0 || nx >= mask.cols || ny < 0 || ny >= mask.rows)){
                        resMask.at<unsigned char>(ny,nx) = 1;
                    }
                }
            }}}}

    return resMask;
}

cv::Mat erode(cv::Mat mask, int r){
    cv::Mat resMask = mask.clone();

    for(int x = 0; x < mask.cols; ++x){
        for(int y = 0; y < mask.rows; ++y){
            if(mask.at<unsigned char>(y,x) == 0){
                for(int dx = -r; dx < r; ++r){
                    for(int dy = -r; dy < r; ++r){
                        int nx = x + dx;
                        int ny = y + dy;
                        if(!(nx<0 || nx >= mask.cols || ny < 0 || ny >= mask.rows)){
                            resMask.at<unsigned char>(ny,nx) = 0;
                        }
                    }
                }}}}

    return resMask;
}