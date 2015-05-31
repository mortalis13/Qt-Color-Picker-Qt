#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include <QtCore>
#include <QColor>

#include <QObject>
#include <QClipboard>

#include "hselector.h"
#include "svselector.h"

#include "vars.h"


class ColorProcessor : public QObject
{
  Q_OBJECT

public:
  explicit ColorProcessor(HSelector* hSelector, SVSelector* svSelector, QObject* parent=0);

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
  HSelector* hSelector;
  SVSelector* svSelector;
  QClipboard* clip;
  
  QColor getColorHSV(QString HSV_Text);
  QColor getColorRGB(QString RGB_Text);
  QColor getColorCMYK(QString CMYK_Text);
  QColor getColorHex(QString Hex_Text);

};

#endif // COLORPROCESSOR_H
