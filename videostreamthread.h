#ifndef VIDEOSTREAMTHREAD_H
#define VIDEOSTREAMTHREAD_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <QUdpSocket>
#include <QAbstractSocket>
#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class VideoStreamThread : public QThread
{
    Q_OBJECT
public:
    VideoStreamThread(QObject *parent = 0);
    ~VideoStreamThread();

    void startReceiving();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    QImage convertOpenCVMatToQtQImage(cv::Mat);

    QMutex mutex;
    QWaitCondition condition;
    bool restart;
    bool abort;

signals:
    void sendImage(cv::Mat);

};

#endif // VIDEOSTREAMTHREAD_H
