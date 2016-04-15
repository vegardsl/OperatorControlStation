#ifndef VIDEOUDPCLIENT_H
#define VIDEOUDPCLIENT_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <QUdpSocket>
#include <QAbstractSocket>

class VideoUdpClient : public QThread
{
public:
    VideoUdpClient(QObject *parent = 0);
    ~VideoUdpClient();

    void startReceiving();
    void initSocket();
protected:
    void run() Q_DECL_OVERRIDE;

private:

    void processDatagram(QByteArray datagram);

    QMutex mutex;
    QWaitCondition condition;
    bool restart;
    bool abort;

    QUdpSocket *udpSocket;
    QByteArray message_word;
    qreal linearCommand, angularCommand;

signals:
    void setCurrentCommand(qreal _linearCommand, qreal _angularCommand);

private slots:
   void  readPendingDatagrams();
};

#endif // VIDEOUDPCLIENT_H
