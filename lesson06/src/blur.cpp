#include "blur.h"

#include <libutils/rasserts.h>

cv::Mat blur(cv::Mat image, double sigma) {
    // TODO формулу весов можно найти тут:
    int height = image.rows;
    int width = image.cols;
    cv::Mat img = image.clone();

    int r = 10;


    for(int i = 0; i < image.cols; ++i){
        for(int j = 0; j < image.rows; ++j){
            cv::Vec3b color = img.at<cv::Vec3b>(j, i);
            double blue = 0;
            double green = 0;
            double red = 0;
            double ves = 0;

            for(int di = -r; di<=r; ++di){
                for(int dj = -r; dj<=r; ++dj){
                    if(i+di >= 0 && i+di < width && j+dj >= 0 && j+dj < height) {
                        cv::Vec3b colorD = img.at<cv::Vec3b>(j, i);
                        unsigned char blueD = colorD[0];
                        unsigned char greenD = colorD[1];
                        unsigned char redD = colorD[2];

                        blue +=  (blueD * gauss(dj,di,sigma));
                        green +=  (greenD * gauss(dj,di,sigma));
                        red +=  (redD * gauss(dj,di,sigma));
                        ves += gauss(dj,di,sigma);
                    }
                }
            }

            image.at<cv::Vec3b>(j, i) = cv::Vec3b((unsigned char)(blue/ves), (unsigned char)(green/ves), (unsigned char)(red/ves));}}
    return image;
}

double gauss(int x, int y, double sigma){
    return (1/(2*3.14*sigma*sigma))*pow(2.7, -((x*x + y*y)/(2*sigma*sigma)));
}