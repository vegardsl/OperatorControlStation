#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robotcontrolwidget.h"

#include <QTime>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "Setting up QUI";

    ui->setupUi(this);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    RobotControlWidget *robotControlWidget = new RobotControlWidget;
    ui->centerDisplayLayout->addWidget(robotControlWidget);

    leftLayoutStack->addWidget(leftOffStatusDisplay);
    leftLayoutStack->addWidget(videoDisplay);


    rightDisplayStack->addWidget(rightOffStatusDisplay);

    ui->rightDisplayLayout->addWidget(rightDisplayStack);

    ui->leftDisplayLayout->addLayout(leftLayoutStack);

    qDebug() << "Setting up signals and slots";

    connect(this, &MainWindow::setLeftDisplay,
            leftLayoutStack,&QStackedLayout::setCurrentIndex);

    connect(robotControlWidget, SIGNAL(updateCommandTransmitter(qreal,qreal)),
            &tcpClientThread, SLOT(setCurrentCommand(qreal,qreal)));

    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(&videoStreamThread, &VideoStreamThread::sendImage,
            this, &MainWindow::receiveImage);

    qDebug() << "Startin video streamer";
    videoStreamThread.startReceiving();
    tcpClientThread.startCommunication();
    qDebug() << "Setup complete";
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
 * Function is copied from:
 * https://github.com/MicrocontrollersAndMore/OpenCV_3_Windows_10_Installation_Tutorial/blob/master/CannyStillWithQtGUI.cpp
 */
QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage(); // return a blank QImage if the above did not work
}

void MainWindow::receiveImage(cv::Mat cvImage)
{
    QImage qImage = convertOpenCVMatToQtQImage(cvImage);
    videoDisplay->setPixmap(QPixmap::fromImage(qImage));
}

void MainWindow::on_cameraButton_clicked()
{
    emit(setLeftDisplay(1));
}

