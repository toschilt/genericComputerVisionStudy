#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
    Prática 6 - Treinamento de Visão
    - Obtendo vídeo da webcam do computador
    - Tratamento do vídeo com loop infinito
    - Vídeo convertido para grayscale.
*/

int main(int argc, char *argv[])
{
    cv::VideoCapture webcam(0, cv::CAP_V4L2);
    cv::namedWindow("originalVideo", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("grayscaleVideo", cv::WINDOW_AUTOSIZE);

    double fps;
    fps = webcam.get(cv::CAP_PROP_FPS);

    webcam.set(cv::CAP_PROP_FRAME_WIDTH, 160);
    webcam.set(cv::CAP_PROP_FRAME_HEIGHT, 120);

    if(!webcam.isOpened())
    {
        std::cout << "Erro em abrir o vídeo!" << std::endl;
        return -1;
    }

    std::cout << 
         "(" << 
         webcam.get(cv::CAP_PROP_FRAME_WIDTH) << 
         ", " <<
         webcam.get(cv::CAP_PROP_FRAME_HEIGHT) <<
         ")" <<
         std::endl;

    while(true)
    {
        cv::Mat frame, grayscaleFrame;
        webcam.read(frame);

        cv::cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);

        std::cout << "FPS = " << fps << std::endl;

        cv::imshow("originalVideo", frame);
        cv::imshow("grayscaleVideo", grayscaleFrame);

        if(cv::waitKey(10) == 'q')
        {
            std::cout << "Vídeo finalizado!" << std::endl;
            break;
        }
    }

    cv::destroyAllWindows();  

    return 0;
}