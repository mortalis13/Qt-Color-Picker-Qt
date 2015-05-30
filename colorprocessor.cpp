
#include "colorprocessor.h"

ColorProcessor::ColorProcessor(HueBar *hueBar, SatValueSelector *satValueSelector){
  this->hueBar=hueBar;
  this->satValueSelector=satValueSelector;
}

QString ColorProcessor::getHSV(QColor color){
  QString res;

  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

  res=QString("%1 %2 %3").arg(h).arg(s).arg(v);
  return res;
}

QString ColorProcessor::getRGB(QColor color){
  QString res;
  
  int r=color.red();
  int g=color.green();
  int b=color.blue();

  res=QString("%1 %2 %3").arg(r).arg(g).arg(b);
  
  return res;
}

QString ColorProcessor::getCMYK(QColor color){
  QString res;

  int c=color.cyan();
  int m=color.magenta();
  int y=color.yellow();
  int k=color.black();

  res=QString("%1 %2 %3 %4").arg(c).arg(m).arg(y).arg(k);

  return res;
}

QString ColorProcessor::getHex(QColor color){
  QString res;
  
  res=color.name();
  res=res.replace("#", "");

  return res;
}

QColor ColorProcessor::getColorHSV(QString HSV){
  QStringList list;
  QColor color;

  list=HSV.split(" ");
  int h=list[0].toInt();
  int s=list[1].toInt();
  int v=list[2].toInt();

  color.setHsv(h, s, v);

  return color;
}

QColor ColorProcessor::getColorRGB(QString RGB){
  QStringList list;
  QColor color;

  list=RGB.split(" ");
  int r=list[0].toInt();
  int g=list[1].toInt();
  int b=list[2].toInt();

  color.setRgb(r, g, b);

  return color;
}

void ColorProcessor::updateColorHSV(QString HSV){
  QColor color=getColorHSV(HSV);

  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

//  qDebug() << QString("%1, %2, %3").arg(h).arg(s).arg(v);

  hueBar->setHueFromText(h);
  satValueSelector->setSaturation(s);
  satValueSelector->setValue(v);

  satValueSelector->updateColor();
}

void ColorProcessor::updateColorRGB(QString RGB){
  QColor color=getColorRGB(RGB);

  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

//  qDebug() << QString("%1, %2, %3").arg(h).arg(s).arg(v);

  hueBar->setHueFromText(h);
  satValueSelector->setSaturation(s);
  satValueSelector->setValue(v);

  satValueSelector->updateColor();
}
