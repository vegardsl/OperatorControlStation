#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T18:02:43
#
#-------------------------------------------------

QT       += core gui widgets network

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OperatorControlStation
TEMPLATE = app

OPENCV_BUILD = $$(OPENCV_BUILD)

CONFIG(release, release|debug){
    LIBS += -L$$OPENCV_BUILD\x64\vc14\lib -lopencv_world310d
}

CONFIG(debug, release|debug){
    LIBS += -L$$OPENCV_BUILD\x64\vc14\lib -lopencv_world310d
}

INCLUDEPATH += $$OPENCV_BUILD\include

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
    displaycontrolwidget.cpp \
    videoudpclient.cpp

HEADERS  += mainwindow.h \
    controlwidget.h \
    controlnode.h \
    tcpclientthread.h \
    mapwidget.h \
    robotstatuswidget.h \
    videostreamwidget.h \
    offstatusdisplay.h \
    displayselectordial.h \
    displaycontrolwidget.h \
    videoudpclient.h

FORMS    += mainwindow.ui
