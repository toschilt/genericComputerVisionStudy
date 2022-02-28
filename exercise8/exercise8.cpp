#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 8 - Treinamento de Visão
    - Identificação de contronos pelo método Canny
    - Detecção de linhas
    - Detecção de círculos
*/

void detectLines(cv::Mat outputImage, 
                 cv::Mat edgesImage,
                 std::vector<cv::Vec4i> lines)
{
    cv::HoughLinesP(edgesImage, lines, 1, CV_PI/180, 50, 50, 10);

    for(int i = 0; i < lines.size(); i++)
    {
        cv::line(outputImage,
                 cv::Point(lines[i][0], lines[i][1]),
                 cv::Point(lines[i][2], lines[i][3]),
                 cv::Scalar(255, 0, 255),
                 3);
    }
}

void detectCircles(cv::Mat outputImage,
                   cv::Mat grayscaleImage,
                   std::vector<cv::Vec3f> circles)
{
    cv::HoughCircles(grayscaleImage,
                     circles,
                     cv::HOUGH_GRADIENT,
                     1,
                     grayscaleImage.rows/16,
                     100, 40, 20, 130);

    for(int i = 0; i < circles.size(); i++)
    {
        int x = circles[i][0];
        int y = circles[i][1];
        int radius = circles[i][2];

        cv::circle(outputImage,
                   cv::Point(x, y),
                   radius,
                   cv::Scalar(255, 0, 0),
                   10, -1);

        cv::circle(outputImage,
                   cv::Point(x, y),
                   3,
                   cv::Scalar(255, 0, 0),
                   3, -1);
    }
}

int main(int argc, char *argv[])
{
    cv::namedWindow("originalImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("grayscaleImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("cannyImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("resultImage", cv::WINDOW_AUTOSIZE);

    cv::Mat originalImage, grayscaleImage, cannyImage, resultImage;

    originalImage = cv::imread("Moedas e linhas.jpeg");
    cv::resize(originalImage,
               originalImage,
               cv::Size(720, 900));

    cv::cvtColor(originalImage,
                 grayscaleImage,
                 cv::COLOR_BGR2GRAY);

    cv::Canny(originalImage,
              cannyImage,
              150,
              300,
              3);

    cv::GaussianBlur(cannyImage, cannyImage, cv::Size(3, 3), 0, 0);

    originalImage.copyTo(resultImage);

    std::vector<cv::Vec4i> lines;
    std::vector<cv::Vec3f> circles;
    detectLines(resultImage, cannyImage, lines);
    detectCircles(resultImage, grayscaleImage, circles);

    cv::imshow("originalImage", originalImage);
    cv::imshow("grayscaleImage", grayscaleImage);
    cv::imshow("cannyImage", cannyImage);
    cv::imshow("resultImage", resultImage);

    cv::waitKey(0);
    cv::destroyAllWindows();  

    return 0;
}