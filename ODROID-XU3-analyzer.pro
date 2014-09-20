#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T15:31:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ODROID-XU3-analyzer
TEMPLATE = app


SOURCES += main.cpp\
        analyzerwindow.cpp \
    takevalue.cpp \
    qcustomplot.cpp

HEADERS  += analyzerwindow.h \
    takevalue.h \
    qcustomplot.h

FORMS    += analyzerwindow.ui

QT += printsupport
