#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

/*
    Prática 1 - Treinamento de Visão
    - Cria janelas nomeadas
    - Lê imagens .png
    - Mostra imagens na tela
    - Obtém metadados da imagem carregada
*/
int main(int argc, char *argv[])
{
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("GrayImage", cv::WINDOW_AUTOSIZE);

    cv::Mat image;
    cv::Mat grayImage;

    image = cv::imread("lena.png");
    grayImage = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);

    cv::imshow("Image", image);
    cv::imshow("GrayImage", grayImage);

    int width = image.cols;
    int height = image.rows;

    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "RGB Channels: " << image.channels() << std::endl;
    std::cout << "Grayscale Channels: " << grayImage.channels() << std::endl;
    std::cout << "RGB Data Type: " << image.type() << std::endl;
    std::cout << "Grayscale Data Type: " << grayImage.type() << std::endl;

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}