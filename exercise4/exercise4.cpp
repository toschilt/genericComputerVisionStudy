#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 4 - Treinamento de Visão
    - Criação de polígonos com vetor de pontos
    - Preenchimento de polígonos convexos
    - Criação de círculo, retângulo e linha.
*/

int main(int argc, char *argv[])
{
    cv::namedWindow("brazilFlag", cv::WINDOW_AUTOSIZE);
    
    cv::Mat brazilFlag;
    int height = 300;
    int width = 500;

    //Fundo verde
    brazilFlag = cv::Mat(height, width, CV_8UC3, cv::Scalar(40, 180, 70));

    //Losango amarelo
    //OBS: a origem do sistema de coords na imagem é no canto superior esquerdo.
    //Eixos crescem para baixo e para direita.
    std::vector<cv::Point> diamondShape;
    diamondShape.push_back(cv::Point(width*0.1, height/2));
    diamondShape.push_back(cv::Point(width/2, height*0.1));
    diamondShape.push_back(cv::Point(width*0.9, height/2));
    diamondShape.push_back(cv::Point(width*0.1, height/2));
    diamondShape.push_back(cv::Point(width/2, height*0.9));
    diamondShape.push_back(cv::Point(width*0.9, height/2));
    cv::fillConvexPoly(brazilFlag, diamondShape, cv::Scalar(0, 255, 255));

    //Círculo azul
    int radius = 80;
    cv::circle(brazilFlag, 
               cv::Point(width/2, height/2), 
               radius, 
               cv::Scalar(255, 0, 0),
               -1);

    //Faixa branca
    cv::line(brazilFlag, 
             cv::Point(width/2 - radius, height/2 - height*0.07),
             cv::Point(width/2 + radius, height/2 + height*0.01),
             cv::Scalar(255, 255, 255),
             15);

    //Contorno preto
    cv::rectangle(brazilFlag,
                  cv::Point(0, 0),
                  cv::Point(width, height),
                  cv::Scalar(0, 0, 0),
                  15);

    cv::imshow("brazilFlag", brazilFlag);

    cv::waitKey(0);
    cv::destroyAllWindows();   

    return 0;
}