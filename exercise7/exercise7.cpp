#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 7 - Treinamento de Visão
    - Abrindo um vídeo gravado
    - Binarização a partir de thresholds
    - Erosão e Dilatação
    - Função de tracking para identificação de contornos e centróides.
*/

void tracking(cv::Mat outputImage, cv::Mat binaryImage)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    std::vector<cv::Moments> m(contours.size());
    for(int i = 0; i < contours.size(); i++)
    {
        m[i] = cv::moments(contours[i]);
    }

    std::vector<cv::Point2f> centroids(contours.size());
    for(int i = 0; i < contours.size(); i++)
    {
        float pos_x = m[i].m10/m[i].m00;
        float pos_y = m[i].m01/m[i].m00;
        centroids[i] = cv::Point2f(pos_x, pos_y);
    }

    for(int i = 0; i < contours.size(); i++)
    {
        if(cv::contourArea(contours[i]) > 100)
        {
            cv::drawContours(outputImage, contours, i, cv::Scalar(0, 0, 255), 2, 8, hierarchy, 0, cv::Point());
            cv::circle(outputImage, centroids[i], 5, cv::Scalar(0, 255, 0), -1);
        }
    }
}

int main(int argc, char *argv[])
{

    cv::VideoCapture originalVideo("geometria.mp4");

    cv::namedWindow("originalVideo", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("hsvVideo", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("control", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("mask", cv::WINDOW_AUTOSIZE);

    if(!originalVideo.isOpened())
    {
        std::cout << "Erro em abrir o vídeo!" << std::endl;
        return -1;
    }

    int hLow = 97, sLow = 80, vLow = 0;
    int hHigh = 150, sHigh = 255, vHigh = 255;

    cv::createTrackbar("hLow", "control", &hLow, 179);
    cv::createTrackbar("hHigh", "control", &hHigh, 179);
    cv::createTrackbar("sLow", "control", &sLow, 255);
    cv::createTrackbar("sHigh", "control", &sHigh, 255);
    cv::createTrackbar("vLow", "control", &vLow, 255);
    cv::createTrackbar("vHigh", "control", &vHigh, 255);

    while(true)
    {
        cv::Mat frame, hsvFrame, thresholdFrame;

        originalVideo.read(frame);
        if(frame.empty())
        {
            std::cout << "Fim do vídeo!" << std::endl;
            break;
        }

        cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
        cv::inRange(hsvFrame, 
                    cv::Scalar(hLow, sLow, vLow),
                    cv::Scalar(hHigh, sHigh, vHigh),
                    thresholdFrame);

        cv::erode(thresholdFrame,
                  thresholdFrame,
                  cv::getStructuringElement(cv::MORPH_ELLIPSE, 
                                            cv::Size(5, 5)));

        cv::dilate(thresholdFrame,
                   thresholdFrame,
                   cv::getStructuringElement(cv::MORPH_ELLIPSE, 
                                             cv::Size(5, 5)));

        cv:tracking(frame, thresholdFrame);

        cv::imshow("originalVideo", frame);
        cv::imshow("hsvVideo", hsvFrame);
        cv::imshow("mask", thresholdFrame);

        if(cv::waitKey(20) == 'q')
        {
            std::cout << "Vídeo interrompido!" << std::endl;
            break;
        }
    }

    cv::destroyAllWindows();  

    return 0;
}