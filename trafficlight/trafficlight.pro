#-------------------------------------------------
#
# Project created by QtCreator 2018-09-17T18:31:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trafficlight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    car.cpp \
    control.cpp \
    light.cpp

HEADERS  += mainwindow.h \
    car.h \
    light.h \
    control.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
