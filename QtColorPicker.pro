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
        Views/mainwindow.cpp \
\
        Widgets/ColorWidgets/colorsample.cpp \
        Widgets/ColorWidgets/hselector.cpp \
        Widgets/ColorWidgets/svselector.cpp \
        Widgets/colortext.cpp \
\
        Service/services.cpp \
        Service/validator.cpp \
        Service/vars.cpp \
\
        Models/colorprocessor.cpp \
\
        Test/testpaint.cpp \
    Views/sliders.cpp \
    Widgets/Sliders/hslider.cpp \
    Widgets/Sliders/sslider.cpp \
    Widgets/Sliders/vslider.cpp

HEADERS  += Views/mainwindow.h \
\
        Widgets/ColorWidgets/colorsample.h \
        Widgets/ColorWidgets/hselector.h \
        Widgets/ColorWidgets/svselector.h \
        Widgets/colortext.h \
\
        Service/services.h \
        Service/validator.h \
        Service/vars.h \
\
        Models/colorprocessor.h \
\
        Test/testpaint.h \
    Views/sliders.h \
    Widgets/Sliders/hslider.h \
    Widgets/Sliders/sslider.h \
    Widgets/Sliders/vslider.h

FORMS    += Views/mainwindow.ui \
            Views/mainwindow1.ui \
            Views/mainwindow2.ui \
            Views/dialog.ui \
    Views/sliders.ui
