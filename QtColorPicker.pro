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
    Widgets/Sliders/HSV/hslider.cpp \
    Widgets/Sliders/HSV/sslider.cpp \
    Widgets/Sliders/HSV/vslider.cpp \
\
    Widgets/Sliders/RGB/rslider.cpp \
    Widgets/Sliders/RGB/gslider.cpp \
    Widgets/Sliders/RGB/bslider.cpp \

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
    Widgets/Sliders/HSV/hslider.h \
    Widgets/Sliders/HSV/sslider.h \
    Widgets/Sliders/HSV/vslider.h \
\
    Widgets/Sliders/RGB/rslider.h \
    Widgets/Sliders/RGB/gslider.h \
    Widgets/Sliders/RGB/bslider.h \
    
FORMS    += Views/mainwindow.ui \
            Views/dialog.ui \
    Views/sliders.ui
