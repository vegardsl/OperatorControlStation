#include "videostreamwidget.h"

#include <QGraphicsItem>
#include <QDebug>
#include <opencv2/opencv.hpp>


VideoStreamWidget::VideoStreamWidget(QWidget *parent) : QGraphicsView(parent)
{
    QImage *image = new QImage(640,480,QImage::Format_RGB888);
    image->fill(Qt::red);

    videoDisplay->setPixmap(QPixmap::fromImage(*image));
    //QGraphicsPixmapItem videoDisplay.setPixmap(QPixmap::fromImage(image));

    //videoPixmap->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    //videoPixmap->setPixmap(QPixmap::fromImage(*image));
    //videoDisplay = QPixmap::fromImage(image);

    //QGraphicsPixmapItem videoDisplay;
    //videoDisplay.setPixmap(QPixmap::fromImage(image));
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    setMinimumSize(640, 480);
    setMaximumSize(640, 480);

    //videoPixmap->setPixmap(QPixmap::fromImage(image));
    //videoPixmap->setZValue(2);

    QGraphicsEllipseItem* deadZoneIndicator = new QGraphicsEllipseItem(-20,-20,40,40);
    deadZoneIndicator->setBrush(Qt::green);
    deadZoneIndicator->setOpacity(0.3);
    deadZoneIndicator->setZValue(-2);

    scene->addItem(deadZoneIndicator);

    //scene->addItem(&videoDisplay);
    //scene->addPixmap(QPixmap::fromImage(*image));
    //scene->addPixmap(videoDisplay); // Does not crash
    //scene->addItem(videoPixmap);
    //scene->addItem(videoDisplay); // This cause a crash
    //QGraphicsView view(scene);
    //view.show();
}

QImage VideoStreamWidget::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}

void VideoStreamWidget::receiveImage(cv::Mat cvImage)
{
    QImage qImage = convertOpenCVMatToQtQImage(cvImage);
    //videoDisplay = QPixmap::fromImage(qImage);
    qDebug() << "Image update";
    //videoDisplay(QPixmap::fromImage(qImage));
    //videoDisplay->setPixmap(QPixmap::fromImage(qImage));
}
