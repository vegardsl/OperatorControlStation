#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpclientthread.h"
#include "videostreamthread.h"
#include "robotstatuswidget.h"
//#include "videostreamwidget.h"
#include "offstatusdisplay.h"

#include <QMainWindow>
#include <QStackedWidget>
#include <QStackedLayout>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//#include <QImage>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void receiveImage(cv::Mat);

private slots:

    void on_cameraButton_clicked();

private:
    Ui::MainWindow *ui;

    TcpClientThread tcpClientThread;
    VideoStreamThread videoStreamThread;

    //VideoStreamWidget *videoStreamWidget = new VideoStreamWidget;
    RobotStatusWidget *robotStatusWidget = new RobotStatusWidget;
    OffStatusDisplay *leftOffStatusDisplay = new OffStatusDisplay;
    OffStatusDisplay *rightOffStatusDisplay = new OffStatusDisplay;

    QStackedWidget *leftDisplayStack = new QStackedWidget;
    QStackedWidget *rightDisplayStack = new QStackedWidget;

    QStackedLayout *leftLayoutStack = new QStackedLayout;

    QLabel *videoDisplay = new QLabel(this);

    const int LEFT = 0;
    const int RIGHT = 1;

    QImage convertOpenCVMatToQtQImage(cv::Mat);

signals:
    void setLeftDisplay(int);
};

#endif // MAINWINDOW_H
