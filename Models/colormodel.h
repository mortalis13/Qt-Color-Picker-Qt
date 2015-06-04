#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QtCore>
#include <QColor>

#include <QObject>

#include "Views/mainwindow.h"
#include "Views/sliders.h"

#include "Models/colorprocessor.h"
#include "Widgets/ColorWidgets/hselector.h"
#include "Widgets/ColorWidgets/svselector.h"

#include "Service/vars.h"

class MainWindow;

class ColorModel : public QObject
{
  Q_OBJECT

public:
  explicit ColorModel(HSelector* hSelector, SVSelector* svSelector,
                      ColorProcessor *colorProcessor, SlidersColorModel *slidersColorModel, 
                      MainWindow *view, 
                      QObject* parent=0);

private:
  void addActions();
  
  void connectHSV();
  void connectRGB();
  void disconnectRGB();
  void connectCMYK();
  void disconnectCMYK();
  
  void changeRGB(int pos, int val);
  void changeCMYK(int pos, int val);


signals:
  void hueChanged(QColor);
  void saturationChanged(QColor);
  void valueChanged(QColor);
  void RGBChanged(QColor);
  void CMYKChanged(QColor);

public slots:
  void changeHue(QColor color);
  void changeSaturation(QColor color);
  void changeValue(QColor color);
  
  void changeRed(QColor color);
  void changeGreen(QColor color);
  void changeBlue(QColor color);
  
  void changeCyan(QColor color);
  void changeMagenta(QColor color);
  void changeYellow(QColor color);
  void changeBlack(QColor color);

private:
  HSelector* hSelector;
  SVSelector* svSelector;

  ColorProcessor* colorProcessor;
  SlidersColorModel *slidersColorModel;
  
  MainWindow* view;
  
};

#endif // COLORMODEL_H
