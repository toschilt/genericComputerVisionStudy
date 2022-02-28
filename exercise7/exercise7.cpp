#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 7 - Treinamento de Visão
*/

int main(int argc, char *argv[])
{

    cv::namedWindow("originalVideo", cv::WINDOW_AUTOSIZE);

    cv::waitKey(0);
    cv::destroyAllWindows();  

    return 0;
}