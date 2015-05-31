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
    colorsample.cpp \
testpaint.cpp \ 
colorprocessor.cpp \
    services.cpp \
    colortext.cpp \
    validator.cpp \
    vars.cpp \
    hselector.cpp \
    svselector.cpp

HEADERS  += mainwindow.h \
    colorsample.h \
testpaint.h \
colorprocessor.h \
    services.h \
    colortext.h \
    validator.h \
    vars.h \
    hselector.h \
    svselector.h

FORMS    += mainwindow.ui \
    dialog.ui
