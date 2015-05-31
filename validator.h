#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QColor>

#include "vars.h"


class Validator : public QObject
{
  Q_OBJECT
  
public:
  explicit Validator(QObject *parent = 0);
  
  static bool checkColorText(QString text, Vars::ColorType colorType=Vars::HSV);
  
  static bool checkValueHSV(QString text);
  static bool checkValueRGB(QString text);
  static bool checkValueCMYK(QString text);
  static bool checkValueHex(QString text);
  
  static QColor correctColor(QColor color);
  
  static bool checkComponentVal(int val, Vars::ColorType colorType=Vars::HSV, int group=0, int hexLen=0);
  static bool checkValueByType(QString text, Vars::ColorType colorType=Vars::HSV);
  
  
private:
  static int getSizeByType(Vars::ColorType colorType);
  
  
signals:

public slots:

};

#endif // VALIDATOR_H
