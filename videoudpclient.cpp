#include "videoudpclient.h"

#include <opencv2/core.hpp>

VideoUdpClient::VideoUdpClient(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;
}

VideoUdpClient::~VideoUdpClient()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void VideoUdpClient::processDatagram(QByteArray datagram)
{
    //cv::Mat img = cv::zeros(480, 640, CV_8UC3);
    //int imgSize = img.total()*img.elemSize();
/*
    //Receive data here
      for (int i = 0; i < imgSize; i += bytes) {
      if ((bytes = recv(connectSock, sockData +i, imgSize  - i, 0)) == -1) {
        quit("recv failed", 1);
       }
      }

    // Assign pixel value to img

    int ptr=0;
    for (int i = 0;  i < img.rows; i++) {
     for (int j = 0; j < img.cols; j++) {
      img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
      ptr=ptr+3;
      }
     }
    */
    qDebug() << "Received";
}

void VideoUdpClient::initSocket()
{
    //QHostAddress address = QHostAddress("192.168.0.107");
    udpSocket = new QUdpSocket(this);
    if( !(udpSocket->bind(2001)) )
    {
        qDebug() << "Unable to bind";
    }

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    VideoUdpClient::readPendingDatagrams();
}
/*
void VideoUdpClient::startReceiving()
{
    initSocket();
    if (!isRunning()) {
        qDebug() << "Starting video thread.";
        start(LowPriority);
    }
}
*/
void VideoUdpClient::readPendingDatagrams()
{

    qDebug() << "In loop";
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
    /*
            cv::Mat  img = cv::Mat::zeros( 480,640, CV_8UC3);
            int  imgSize = img.total()*img.elemSize();
            QByteArray datagram;
            datagram.resize(imgSize);
    */
    /*
            //Receive data here

            for (int i = 0; i < imgSize; i += bytes) {
                if ((bytes = recv(connectSock, sockData +i, imgSize  - i, 0)) == -1) {
                    quit("recv failed", 1);
                }
                udpSocket->readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);
            }

             // Assign pixel value to img

            int ptr=0;
            for (int i = 0;  i < img.rows; i++) {
                for (int j = 0; j < img.cols; j++) {
                    img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
                    ptr=ptr+3;
                }
            }
    */
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
         processDatagram(datagram);
    }
    //QObject().thread()->usleep(3000);

}

void VideoUdpClient::run()
{

}
