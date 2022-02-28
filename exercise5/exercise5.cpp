#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 5 - Treinamento de Visão
    - Transformação Afim
    - Transformação de Perspectiva
    - Obter coordenadas de um ponto específico da imagem com função de callback.
*/

void getImagePointCallback(int event, int x, int y, int flags, void *userdata)
{
    if(event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    //ETAPA 1
    cv::namedWindow("originalImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("transformedImage", cv::WINDOW_AUTOSIZE);

    cv::Mat originalImage, transformedImage;
    originalImage = cv::imread("triangle.jpg");
    cv::setMouseCallback("originalImage", getImagePointCallback, NULL);
    
    cv::Point2f triangleVertices[3];
    triangleVertices[0] = cv::Point2f(60, 470);
    triangleVertices[1] = cv::Point2f(296, 66);
    triangleVertices[2] = cv::Point2f(524, 471);

    cv::circle(originalImage, triangleVertices[0], 10, cv::Scalar(0, 255, 0), 15);
    cv::circle(originalImage, triangleVertices[1], 10, cv::Scalar(0, 0, 255), 15);
    cv::circle(originalImage, triangleVertices[2], 10, cv::Scalar(255, 0, 0), 15);

    cv::Point2f triangleNewVertices[3];
    triangleNewVertices[0] = cv::Point2f(249, 503);
    triangleNewVertices[1] = cv::Point2f(443, 224);
    triangleNewVertices[2] = cv::Point2f(80, 137);

    cv::Mat affineMatrix;
    affineMatrix = cv::getAffineTransform(triangleVertices, triangleNewVertices);
    cv::warpAffine(originalImage, transformedImage, affineMatrix, originalImage.size());

    cv::imshow("originalImage", originalImage);
    cv::imshow("transformedImage", transformedImage);

    cv::waitKey(0);
    cv::destroyAllWindows();   

    // ---------------------------------------

    //ETAPA2
    cv::namedWindow("originalImage2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("transformedImage2", cv::WINDOW_AUTOSIZE);

    cv::Mat originalImage2, transformedImage2;
    originalImage2 = cv::imread("carta.jpeg");

    cv::resize(originalImage2, originalImage2, cv::Size(500, 500));

    cv::Point2f cardVertices[4];
    cardVertices[0] = cv::Point2f(98, 307);
    cardVertices[1] = cv::Point2f(167, 139);
    cardVertices[2] = cv::Point2f(377, 135);
    cardVertices[3] = cv::Point2f(449, 301);

    cv::Point2f cardNewVertices[4];
    cardNewVertices[0] = cv::Point2f(82, 400);
    cardNewVertices[1] = cv::Point2f(120, 50);
    cardNewVertices[2] = cv::Point2f(388, 50);
    cardNewVertices[3] = cv::Point2f(442, 400);

    cv::Mat perspectiveMatrix;
    perspectiveMatrix = cv::getPerspectiveTransform(cardVertices, cardNewVertices);
    cv::warpPerspective(originalImage2, transformedImage2, perspectiveMatrix, originalImage2.size());

    cv::imshow("originalImage2", originalImage2);
    cv::imshow("transformedImage2", transformedImage2);

    cv::waitKey(0);
    cv::destroyAllWindows();  

    return 0;
}