#-------------------------------------------------
#
# Project created by QtCreator 2015-08-09T16:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QConcurrencySimulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Computer.cpp \
    CPU.cpp \
    Programm.cpp \
    stdafx.cpp \
    filestructure.cpp

HEADERS  += mainwindow.h \
    Computer.h \
    CPU.h \
    Programm.h \
    stdafx.h \
    filestructure.h

FORMS    += mainwindow.ui
