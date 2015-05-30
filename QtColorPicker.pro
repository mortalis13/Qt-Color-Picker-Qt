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
colorprocessor.cpp \
testpaint.cpp 

HEADERS  += mainwindow.h \
    huebar.h \
    colorsample.h \
    satvalueselector.h \
    colorprocessor.h \
testpaint.h

FORMS    += mainwindow.ui \
    dialog.ui
