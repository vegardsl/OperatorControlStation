#include "tcpclientthread.h"

TcpClientThread::TcpClientThread(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;
}

TcpClientThread::~TcpClientThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void TcpClientThread::startCommunication()
{
    if (!isRunning()) {
        start(LowPriority);
    }
}

void TcpClientThread::run()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("192.168.0.107",2000);

    if (socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
    }
    else
    {
        qDebug() << "Not Connected!";
    }

    while(1)
    {
        mutex.lock();

        if(socket->write(message_word.data()) >= 0) {
          if(!socket->flush()) {
            qDebug() << "TCP client socket flush FAILED!";
          }
        }

        mutex.unlock();

        QThread::msleep(100);
    }
}

void TcpClientThread::setCurrentCommand(qreal _linearCommand, qreal _angularCommand)
{
    // TODO: HANDLE OVERFLOW!!!!
    linearCommand = _linearCommand;
    angularCommand = _angularCommand;
    qDebug() << "linearCommand: " << linearCommand << " angularCommand: " << angularCommand;

    mutex.lock();

    message_word.clear();
    message_word.resize(10);
    message_word[0] = 0x3a; // ":"
    message_word[1] = 0x73; // "s"

    if(linearCommand < 0)
    {
        message_word[2] = 0x2d; // "-"
    }
    else
    {
        message_word[2] = 0x2b; // "+"
    }
    message_word[3] = abs(100*linearCommand);

    message_word[4] = 0x61;
    if(angularCommand < 0)
    {
        message_word[5] = 0x2d; // "-"
    }
    else
    {
        message_word[5] = 0x2b; // "+"
    }
    message_word[6] = abs(100*angularCommand);
    //qDebug() << abs(100*angularCommand);
    message_word[7] = 0x1b;
    mutex.unlock();
}
