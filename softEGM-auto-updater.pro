#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T14:37:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = softEGM-auto-updater
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    console.cpp

HEADERS  += maindialog.h \
    console.h

FORMS    += maindialog.ui

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    images.qrc \
    data.qrc
