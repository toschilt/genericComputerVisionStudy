#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 2 - Treinamento de Visão
    - Conversão de imagens para espaços de cores (RGB, HSV e grayscale)
    - Acesso direto aos pixels de uma imagem (escurecimento)
    - Criação de uma imagem com cor arbitrária
    - Redimensionamento de uma imagem
    - Salvar imagem em um caminho arbitrário do computador.
*/
int main(int argc, char *argv[])
{
    //ETAPA 1
    cv::namedWindow("originalImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("grayscaleImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("hsvImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("darkerImage", cv::WINDOW_AUTOSIZE);

    cv::Mat originalImage, grayscaleImage, hsvImage, darkerImage;
    originalImage = cv::imread("semear.png");

    cv::cvtColor(originalImage, grayscaleImage, cv::COLOR_BGR2GRAY);
    cv::cvtColor(originalImage, hsvImage, cv::COLOR_BGR2HSV);

    darkerImage = grayscaleImage.clone();
    for(int row = 0; row < darkerImage.rows; row++)
    {
        for(int col = 0; col < darkerImage.cols; col++)
        {
            darkerImage.at<uint8_t>(row, col) *= 0.5;
        }
    }

    cv::imshow("originalImage", originalImage);
    cv::imshow("grayscaleImage", grayscaleImage);
    cv::imshow("hsvImage", hsvImage);
    cv::imshow("darkerImage", darkerImage);

    cv::waitKey(0);
    cv::destroyAllWindows();

    // ---------------------------------------

    //ETAPA2
    cv::namedWindow("whiteImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("resizedImage", cv::WINDOW_AUTOSIZE);

    cv::Mat whiteImage, resizedImage;

    int oldHeight = 300;
    int oldWidth = 300;
    whiteImage = cv::Mat(oldHeight, oldWidth, CV_8UC3, cv::Scalar(255, 255, 255));

    int newHeight = 500;
    int newWidth = 500;
    cv::resize(whiteImage, resizedImage, cv::Size(newHeight, newWidth));

    for(int row = 0; row < resizedImage.rows; row++)
    {
        for(int col = 0; col < resizedImage.cols; col++)
        {
            resizedImage.at<cv::Vec3b>(row, col) = cv::Vec3b(255, rand()%255, rand()%255);
        }
    }

    cv::imshow("whiteImage", whiteImage);
    cv::imshow("resizedImage", resizedImage);

    cv::waitKey(0);
    cv::imwrite("/home/ltoschi/Documents/genericComputerVisionStudy/exercise3/pratica3.png", resizedImage);
    cv::destroyAllWindows();

    return 0;
}