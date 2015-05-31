#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include <QtCore>
#include <QColor>

#include <QObject>
#include <QClipboard>

#include "huebar.h"
#include "satvalueselector.h"

class ColorProcessor : public QObject
{
  Q_OBJECT

public:
  enum ColorType{
    HSV, RGB, CMYK, Hex
  };
  
public:
  explicit ColorProcessor(HueBar* hueBar, SatValueSelector* satValueSelector, QObject* parent=0);

  QString getHSV(QColor color);
  QString getRGB(QColor color);
  QString getCMYK(QColor color);
  QString getHex(QColor color);

  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
  void updateColorCMYK(QString CMYK);
  void updateColorHex(QString Hex);
  
  void updateColor(QColor color);
  
  void copyText(QString text);
  QString pasteText();

signals:
  void updateFinished();

private:
  HueBar* hueBar;
  SatValueSelector* satValueSelector;
  QClipboard* clip;
  
  QColor getColorHSV(QString HSV);
  QColor getColorRGB(QString RGB);
  QColor getColorCMYK(QString CMYK);
  QColor getColorHex(QString Hex);

  // bool checkColorText(QString text, int size);
  // bool checkValueHSV(QString text);
  // bool checkValueRGB(QString text);
  // bool checkValueCMYK(QString text);
  // bool checkValueHex(QString text);
  
  // QColor correctColor(QColor color);
};

#endif // COLORPROCESSOR_H
