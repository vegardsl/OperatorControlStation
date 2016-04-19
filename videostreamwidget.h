#ifndef VIDEOSTREAMWIDGET_H
#define VIDEOSTREAMWIDGET_H

#include <QGraphicsView>
//#include <QtCore>
//#include <QImage>
#include <QLabel>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class VideoStreamWidget : public QGraphicsView
{
    Q_OBJECT
public:
    VideoStreamWidget(QWidget *parent = 0);

private:
    QImage convertOpenCVMatToQtQImage(cv::Mat);
    //QGraphicsPixmapItem videoDisplay;
    //QGraphicsPixmapItem *videoDisplay;
    //QPixmap videoDisplay;
    //QGraphicsPixmapItem *videoPixmap;
    QLabel *videoDisplay = new QLabel(this);

public slots:
    void receiveImage(cv::Mat);
};

#endif // VIDEOSTREAMWIDGET_H
