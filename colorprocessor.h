#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include <QtCore>
#include <QColor>

#include "huebar.h"
#include "satvalueselector.h"

class ColorProcessor
{
public:
  ColorProcessor(HueBar* hueBar, SatValueSelector* satValueSelector);

  QString getHSV(QColor color);
  QString getRGB(QColor color);
  QString getCMYK(QColor color);
  QString getHex(QColor color);

  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
private:
  QColor getColorHSV(QString HSV);
  QColor getColorRGB(QString RGB);
  
  HueBar* hueBar;
  SatValueSelector* satValueSelector;
  
};

#endif // COLORPROCESSOR_H
