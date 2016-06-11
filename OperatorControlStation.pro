#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T18:02:43
#
#-------------------------------------------------

QT       += core gui widgets network

#QMAKE_CXXFLAGS += -std=c++11

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = OperatorControlStation
TEMPLATE = app

OPENCV_BUILD = $$(OPENCV_BUILD)

CONFIG(release, debug|release){
    #LIBS += $$OPENCV_BUILD\\x64\\vc14\\lib\\opencv_world310.lib# -lopencv_world310
    LIBS += C:\\opencv\\build\\x64\\vc14\\lib\\opencv_world310d.lib# -lopencv_world310d
}

CONFIG(debug, debug|release){
    #LIBS += $$OPENCV_BUILD\\x64\\vc14\\lib\\opencv_world310d.lib# -lopencv_world310d
    LIBS += C:\\opencv\\build\\x64\\vc14\\lib\\opencv_world310d.lib# -lopencv_world310d
}

INCLUDEPATH += $$OPENCV_BUILD\include


SOURCES += main.cpp\
        mainwindow.cpp \
    controlnode.cpp \
    tcpclientthread.cpp \
    mapwidget.cpp \
    robotstatuswidget.cpp \
    videostreamwidget.cpp \
    offstatusdisplay.cpp \
    videostreamthread.cpp \
    robotcontrolwidget.cpp

HEADERS  += mainwindow.h \
    controlnode.h \
    tcpclientthread.h \
    mapwidget.h \
    robotstatuswidget.h \
    videostreamwidget.h \
    offstatusdisplay.h \
    videoudpclient.h \
    videostreamthread.h \
    robotcontrolwidget.h

FORMS    += mainwindow.ui
