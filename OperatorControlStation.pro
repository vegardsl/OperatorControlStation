#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T18:02:43
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OperatorControlStation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlwidget.cpp \
    controlnode.cpp \
    tcpclientthread.cpp \
    mapwidget.cpp \
    robotstatuswidget.cpp \
    videostreamwidget.cpp \
    offstatusdisplay.cpp \
    displayselectordial.cpp \
    displaycontrolwidget.cpp

HEADERS  += mainwindow.h \
    controlwidget.h \
    controlnode.h \
    tcpclientthread.h \
    mapwidget.h \
    robotstatuswidget.h \
    videostreamwidget.h \
    offstatusdisplay.h \
    displayselectordial.h \
    displaycontrolwidget.h

FORMS    += mainwindow.ui
