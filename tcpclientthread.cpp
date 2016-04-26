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

    /*
     * Refer to address reservation list under "DHCP/Address Reservation"
     * in the router settings at "192.168.0.1"
     */
    socket->connectToHost("192.168.0.110",2000);

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

    int i = 0;
    message_word[i] = 0x3a; // ":"
    i++;
    if(abs(linearCommand) > 0)
    {
        message_word[i] = 0x73; // "s"
        i++;
        if(linearCommand < 0)
        {
            message_word[i] = 0x2d; // "-"
        }
        else
        {
            message_word[i] = 0x2b; // "+"
        }
        i++;
        message_word[i] = abs(100*linearCommand);
        i++;
    }

    if(abs(angularCommand) > 0)
    {
        message_word[i] = 0x61;
        i++;
        if(angularCommand < 0)
        {
            message_word[i] = 0x2d; // "-"
        }
        else
        {
            message_word[i] = 0x2b; // "+"
        }
        i++;
        message_word[i] = abs(100*angularCommand);
        i++;
        //qDebug() << abs(100*angularCommand);
    }
    message_word[i] = 0x1b;



    for(int j = 0; j<i; j++)
    {
        qDebug() << message_word[j];
    }

    mutex.unlock();
}
