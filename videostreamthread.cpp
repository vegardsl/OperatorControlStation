#include "videostreamthread.h"

VideoStreamThread::VideoStreamThread(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;
}

VideoStreamThread::~VideoStreamThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void VideoStreamThread::startReceiving()
{
    //initSocket();
    if (!isRunning()) {
        qDebug() << "Starting video thread.";
        start(LowPriority);
    }
}

void VideoStreamThread::run()
{
    cv::Mat cvImage;
    cv::VideoCapture cap;
    cap.open("http://192.168.0.110:8080/stream?topic=/openni/rgb/image_raw");
    cv::waitKey(1000);
    if(!cap.isOpened())
    {
        qDebug() << "Failed to open video stream";
        return;
    }
    qDebug() << "Stream opened.";
    while(1)
    {
        cap.read(cvImage);
        //cv::imshow("Image",image);
        if(!cvImage.empty())
        {

            emit(sendImage(cvImage));
        }

        cv::waitKey(30);
        //qDebug() << "streaming...";
    }
}


