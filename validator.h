#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QColor>

class Validator : public QObject
{
  Q_OBJECT
  
  static int getSizeByType(int colorType);

public:
  enum ColorType{
    HSV, RGB, CMYK, Hex
  };
  
public:
  explicit Validator(QObject *parent = 0);
  
  static bool checkColorText(QString text, int colorType=HSV);
  
  static bool checkValueHSV(QString text);
  static bool checkValueRGB(QString text);
  static bool checkValueCMYK(QString text);
  static bool checkValueHex(QString text);
  
  static QColor correctColor(QColor color);
  
  static bool checkComponentVal(int val, int colorType=HSV, int group=0, int hexLen=0);
  static bool checkValueByType(QString text, int colorType=HSV);
  
signals:

public slots:

};

#endif // VALIDATOR_H
