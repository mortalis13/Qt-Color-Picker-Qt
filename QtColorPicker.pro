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
    Views/sliders.cpp \
\
    Widgets/ColorWidgets/colorsample.cpp \
    Widgets/ColorWidgets/hselector.cpp \
    Widgets/ColorWidgets/svselector.cpp \
    Widgets/colortext.cpp \
\    
    Widgets/Sliders/colorslider.cpp \
    Widgets/Sliders/HSV/hsvslider.cpp \
    Widgets/Sliders/RGB/rgbslider.cpp \
    Widgets/Sliders/CMYK/cmykslider.cpp \
\
    Service/services.cpp \
    Service/validator.cpp \
    Service/vars.cpp \
\
    Models/colorprocessor.cpp \
    Models/colormodel.cpp \
    Controllers/sliderscontroller.cpp


HEADERS  += Views/mainwindow.h \
    Views/sliders.h \
\
    Widgets/ColorWidgets/colorsample.h \
    Widgets/ColorWidgets/hselector.h \
    Widgets/ColorWidgets/svselector.h \
    Widgets/colortext.h \
\
    Widgets/Sliders/colorslider.h \
    Widgets/Sliders/HSV/hsvslider.h \
    Widgets/Sliders/RGB/rgbslider.h \
    Widgets/Sliders/CMYK/cmykslider.h \
\    
    Service/services.h \
    Service/validator.h \
    Service/vars.h \
\
    Models/colorprocessor.h \
    Models/colormodel.h \
    Controllers/sliderscontroller.h
    
    
FORMS    += Views/mainwindow.ui \
    Views/sliders.ui
