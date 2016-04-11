#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcpclientthread.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TcpClientThread tcpClientThread;

    const int LEFT = 0;
    const int RIGHT = 1;
};

#endif // MAINWINDOW_H
