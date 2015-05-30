
#include "colorprocessor.h"

ColorProcessor::ColorProcessor(HueBar *hueBar, SatValueSelector *satValueSelector, QObject* parent) : QObject(parent){
  this->hueBar=hueBar;
  this->satValueSelector=satValueSelector;
}

// -------------------------------------------- color strings --------------------------------------------

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

// -------------------------------------------- color objects --------------------------------------------

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

QColor ColorProcessor::getColorCMYK(QString CMYK){
  QStringList list;
  QColor color;

  list=CMYK.split(" ");
  int c=list[0].toInt();
  int m=list[1].toInt();
  int y=list[2].toInt();
  int k=list[3].toInt();

  color.setCmyk(c, m, y, k);

  return color;
}

QColor ColorProcessor::getColorHex(QString Hex){
  QColor color;
  color.setNamedColor("#"+Hex);
  return color;
}

// -------------------------------------------- update color --------------------------------------------

void ColorProcessor::updateColorHSV(QString HSV){
  QColor color=getColorHSV(HSV);
  updateColor(color);
}

void ColorProcessor::updateColorRGB(QString RGB){
  QColor color=getColorRGB(RGB);
  updateColor(color);
}

void ColorProcessor::updateColorCMYK(QString CMYK){
  QColor color=getColorCMYK(CMYK);
  updateColor(color);
}

void ColorProcessor::updateColorHex(QString Hex){
  QColor color=getColorHex(Hex);
  updateColor(color);
}

void ColorProcessor::updateColor(QColor color){
  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

  hueBar->setH(h);
  satValueSelector->setSV(s, v);

  emit updateFinished();
}
