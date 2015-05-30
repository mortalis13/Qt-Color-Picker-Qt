#ifndef COLORPROCESSOR_H
#define COLORPROCESSOR_H

#include <QtCore>
#include <QColor>

class ColorProcessor
{
public:
  ColorProcessor();

  QString getHSV(QColor color);
  QString getRGB(QColor color);
  QString getCMYK(QColor color);
  QString getHex(QColor color);

private:
  
  
};

#endif // COLORPROCESSOR_H
