
#include "colorprocessor.h"

#include <QApplication>

#include "Service/validator.h"


// -------------------------------------------- consts --------------------------------------------

// ------------------------------------------------------------------------------------------------

ColorProcessor::ColorProcessor(HSelector *hSelector, SVSelector *svSelector, QObject* parent) : QObject(parent){
  this->hSelector=hSelector;
  this->svSelector=svSelector;
  clip=QApplication::clipboard();
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

QColor ColorProcessor::getColorHSV(QString HSV_Text){
  QStringList list;
  QColor color;

  list=HSV_Text.split(" ");
  int h=list[0].toInt();
  int s=list[1].toInt();
  int v=list[2].toInt();

  color.setHsv(h, s, v);
  // color=Validator::correctColor(color);

  return color;
}

QColor ColorProcessor::getColorRGB(QString RGB_Text){
  QStringList list;
  QColor color;

  list=RGB_Text.split(" ");
  int r=list[0].toInt();
  int g=list[1].toInt();
  int b=list[2].toInt();

  color.setRgb(r, g, b);
  // color=Validator::correctColor(color);

  return color;
}

QColor ColorProcessor::getColorCMYK(QString CMYK_Text){
  QStringList list;
  QColor color;

  list=CMYK_Text.split(" ");
  int c=list[0].toInt();
  int m=list[1].toInt();
  int y=list[2].toInt();
  int k=list[3].toInt();

  color.setCmyk(c, m, y, k);
  // color=Validator::correctColor(color);

  return color;
}

QColor ColorProcessor::getColorHex(QString Hex_Text){
  QColor color;
  color.setNamedColor("#"+Hex_Text);
  // color=Validator::correctColor(color);

  return color;
}

// -------------------------------------------- update color --------------------------------------------

void ColorProcessor::updateColorHSV(QString HSV_Text){
  if( !Validator::checkColorText(HSV_Text, Vars::HSV) ) return;
  if( !Validator::checkValueHSV(HSV_Text) ) return;

  QColor color=getColorHSV(HSV_Text);
  updateColor(color);
}

void ColorProcessor::updateColorRGB(QString RGB_Text){
  if( !Validator::checkColorText(RGB_Text, Vars::RGB) ) return;
  if( !Validator::checkValueRGB(RGB_Text) ) return;

  QColor color=getColorRGB(RGB_Text);
  updateColor(color);
}

void ColorProcessor::updateColorCMYK(QString CMYK_Text){
  if( !Validator::checkColorText(CMYK_Text, Vars::CMYK) ) return;
  if( !Validator::checkValueCMYK(CMYK_Text) ) return;

  QColor color=getColorCMYK(CMYK_Text);
  updateColor(color);
}

void ColorProcessor::updateColorHex(QString Hex_Text){
  if( !Validator::checkValueHex(Hex_Text) ) return;

  QColor color=getColorHex(Hex_Text);
  updateColor(color);
}

void ColorProcessor::updateColor(QColor color){
  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

  hSelector->setH(h);
  svSelector->setSV(s, v);

  emit updateFinished();
}

// -------------------------------------------- copy color text --------------------------------------------

void ColorProcessor::copyText(QString text){
  clip->setText(text);
}

QString ColorProcessor::pasteText(){
  bool ok;
  QString text=clip->text();
  text=text.replace("#", "");
  
  int len=text.length();
  if(len!=6 && len!=3) return QString();

  text.toInt(&ok, 16);
  if(!ok) return QString();
  
  return text;
}
