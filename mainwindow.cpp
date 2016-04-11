#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlwidget.h"
#include "robotstatuswidget.h"
#include "videostreamwidget.h"
#include "offstatusdisplay.h"
#include "displaycontrolwidget.h"

#include <QTime>
#include <QStackedWidget>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    ControlWidget *controlWidget = new ControlWidget;
    ui->centerDisplayLayout->addWidget(controlWidget);

    DisplayControlWidget *leftDisplayControl = new DisplayControlWidget(0,LEFT);
    DisplayControlWidget *rightDisplayControl = new DisplayControlWidget(0,RIGHT);

    //ui->horizontalPanelLayout->addWidget(leftDisplayControl);
    //ui->horizontalPanelLayout->addWidget(rightDisplayControl);

    VideoStreamWidget *videoStreamWidget = new VideoStreamWidget;
    RobotStatusWidget *robotStatusWidget = new RobotStatusWidget;
    OffStatusDisplay *leftOffStatusDisplay = new OffStatusDisplay;
    OffStatusDisplay *rightOffStatusDisplay = new OffStatusDisplay;

    QStackedWidget *leftDisplayStack = new QStackedWidget;
    QStackedWidget *rightDisplayStack = new QStackedWidget;

    leftDisplayStack->addWidget(leftOffStatusDisplay);
    rightDisplayStack->addWidget(rightOffStatusDisplay);

    ui->leftDisplayLayout->addWidget(leftDisplayControl);
    ui->leftDisplayLayout->addWidget(leftDisplayStack);
    ui->rightDisplayLayout->addWidget(rightDisplayControl);
    ui->rightDisplayLayout->addWidget(rightDisplayStack);

    qDebug() << "Setting up signals and slots";

    connect(controlWidget, SIGNAL(updateCommandTransmitter(qreal,qreal)),
            &tcpClientThread, SLOT(setCurrentCommand(qreal,qreal)));

    tcpClientThread.startCommunication();

    qDebug() << "Setup complete";
}

MainWindow::~MainWindow()
{
    delete ui;
}
