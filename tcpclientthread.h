#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <QTcpSocket>
#include <QAbstractSocket>

class TcpClientThread : public QThread
{
    Q_OBJECT
public:
    TcpClientThread(QObject *parent = 0);
    ~TcpClientThread();

    void startCommunication();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    QMutex mutex;
    QWaitCondition condition;
    bool restart;
    bool abort;

    QTcpSocket *socket;
    QByteArray message_word;
    qreal linearCommand, angularCommand;

public slots:
    void setCurrentCommand(qreal _linearCommand, qreal _angularCommand);

};

#endif // TCPCLIENTTHREAD_H
