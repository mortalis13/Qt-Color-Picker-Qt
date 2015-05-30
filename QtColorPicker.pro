#-------------------------------------------------
#
# Project created by QtCreator 2015-05-28T15:25:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtColorPicker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    huebar.cpp \
    colorsample.cpp \
    satvalueselector.cpp \
testpaint.cpp \ 
colorprocessor.cpp \
    services.cpp

HEADERS  += mainwindow.h \
    huebar.h \
    colorsample.h \
    satvalueselector.h \
testpaint.h \
colorprocessor.h \
    services.h

FORMS    += mainwindow.ui \
    dialog.ui
