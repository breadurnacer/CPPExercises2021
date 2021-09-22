#include "helper_functions.h"

#include <libutils/rasserts.h>


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

    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы

    return largeBackground;
}
