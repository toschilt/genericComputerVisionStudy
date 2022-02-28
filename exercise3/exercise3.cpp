#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 3 - Treinamento de Visão
    - Mover janela para um ponto arbitrário da tela
    - Redimensionar janela para um tamanho arbitrário
    - Criando trackbars
    - Filtros: média, gaussiano, mediana e bilateral 
*/

cv::Mat originalImage, filteredImage;
int averageAmount, gaussianAmount, medianAmount, bilateralAmount;

void averageFilter(int, void*)
{
    int filterSize = 2*averageAmount + 1;
    cv::blur(originalImage, filteredImage, cv::Size(filterSize, filterSize));
    cv::imshow("filteredImage", filteredImage);
}

void gaussianFilter(int, void*)
{
    int filterSize = 2*gaussianAmount + 1;
    cv::GaussianBlur(originalImage, filteredImage, cv::Size(filterSize, filterSize), 0, 0);
    cv::imshow("filteredImage", filteredImage);
}

void medianFilter(int, void*)
{
    int filterSize = 2*medianAmount + 1;
    cv::medianBlur(originalImage, filteredImage, filterSize);
    cv::imshow("filteredImage", filteredImage);
}

void bilateralFilter(int, void*)
{
    int filterSize = 2*medianAmount + 1;
    cv::bilateralFilter(originalImage, filteredImage, filterSize, filterSize*2, filterSize/2);
    cv::imshow("filteredImage", filteredImage);
}

int main(int argc, char *argv[])
{
    cv::namedWindow("originalImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("filteredImage", cv::WINDOW_AUTOSIZE);

    originalImage = cv::imread("pratica3.png");

    cv::moveWindow("originalImage", 700, 500);
    cv::resizeWindow("originalImage", cv::Size(500, 500));

    cv::createTrackbar("Average Filter", "filteredImage", &averageAmount, 15, averageFilter);
    cv::createTrackbar("Gaussian Filter", "filteredImage", &gaussianAmount, 15, gaussianFilter);
    cv::createTrackbar("Median Filter", "filteredImage", &medianAmount, 15, medianFilter);
    cv::createTrackbar("Bilateral Filter", "filteredImage", &bilateralAmount, 15, bilateralFilter);

    cv::imshow("originalImage", originalImage);

    cv::waitKey(0);
    cv::destroyAllWindows();   

    return 0;
}