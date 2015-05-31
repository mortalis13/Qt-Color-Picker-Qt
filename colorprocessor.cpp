
#include "colorprocessor.h"

#include <QApplication>


// -------------------------------------------- consts --------------------------------------------

const int minH=0;
const int maxH=360;
const int minS=0;
const int maxS=255;
const int minV=0;
const int maxV=255;

const int minRGB=0;
const int maxRGB=255;

const int minC=0;
const int maxC=255;
const int minM=0;
const int maxM=255;
const int minY=0;
const int maxY=255;
const int minK=0;
const int maxK=255;

const int minHex=0;
const int maxHex=255;
const int minSHex=0;
const int maxSHex=15;

// ----------------------------------------------------------------------------------------------------

ColorProcessor::ColorProcessor(HueBar *hueBar, SatValueSelector *satValueSelector, QObject* parent) : QObject(parent){
  this->hueBar=hueBar;
  this->satValueSelector=satValueSelector;
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

// -------------------------------------------- checks --------------------------------------------

bool ColorProcessor::checkColorText(QString text, int size){
  QStringList list;
  list=text.split(" ");
  if(list.size()<size) return false;

  foreach(QString comp, list){
    if(!comp.length())
      return false;
  }

  foreach(QString comp, list){
    bool ok;
    int val=comp.toInt(&ok);
    if(!ok) return false;
  }

  return true;
}

bool ColorProcessor::checkValueHSV(QString text){
  QStringList list;
  list=text.split(" ");

  int h=list[0].toInt();
  int s=list[1].toInt();
  int v=list[2].toInt();

  if(h<minH || h>maxH) return false;
  if(s<minH || s>maxH) return false;
  if(v<minH || v>maxH) return false;

  return true;
}

bool ColorProcessor::checkValueRGB(QString text){
  QStringList list;
  list=text.split(" ");

  int r=list[0].toInt();
  int g=list[1].toInt();
  int b=list[2].toInt();

  if(r<minRGB || r>maxRGB) return false;
  if(g<minRGB || g>maxRGB) return false;
  if(b<minRGB || b>maxRGB) return false;

  return true;
}

bool ColorProcessor::checkValueCMYK(QString text){
  QStringList list;
  list=text.split(" ");

  int c=list[0].toInt();
  int m=list[1].toInt();
  int y=list[2].toInt();
  int k=list[3].toInt();

  if(c<minC || c>maxC) return false;
  if(m<minM || m>maxM) return false;
  if(y<minY || y>maxY) return false;
  if(k<minK || k>maxK) return false;

  return true;
}

bool ColorProcessor::checkValueHex(QString text){
  int len=text.length();
  if( len!=6 && len!=3 ) return false;
  
  bool ok;
  int factor=len/3;

  for(int i=0; i<3; i++){
    QString comp = text.mid(i*factor, factor);
    int val=comp.toInt(&ok, 16);
    if(!ok) return false;

    if(len==3)
      if(val<minSHex || val>maxSHex) return false;
    else
      if(val<minHex || val>maxHex) return false;
  }

  return true;
}

// -------------------------------------------- color objects --------------------------------------------

QColor ColorProcessor::correctColor(QColor color){
  QColor c;

  int h=color.hue();
  int s=color.saturation();
  int v=color.value();

  h=qMax(minH, h);
  h=qMin(maxH, h);

  s=qMax(minH, s);
  s=qMin(maxH, s);

  v=qMax(minH, v);
  v=qMin(maxH, v);

  c.setHsv(h, s, v);
  return c;
}

QColor ColorProcessor::getColorHSV(QString HSV){
  QStringList list;
  QColor color;

  list=HSV.split(" ");
  int h=list[0].toInt();
  int s=list[1].toInt();
  int v=list[2].toInt();

  color.setHsv(h, s, v);
  color=correctColor(color);

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
  color=correctColor(color);

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
  color=correctColor(color);

  return color;
}

QColor ColorProcessor::getColorHex(QString Hex){
  QColor color;
  color.setNamedColor("#"+Hex);
  color=correctColor(color);

  return color;
}

// -------------------------------------------- update color --------------------------------------------

void ColorProcessor::updateColorHSV(QString HSV){
  if( !checkColorText(HSV, 3) ) return;
  if( !checkValueHSV(HSV) ) return;

  QColor color=getColorHSV(HSV);
  updateColor(color);
}

void ColorProcessor::updateColorRGB(QString RGB){
  if( !checkColorText(RGB, 3) ) return;
  if( !checkValueRGB(RGB) ) return;

  QColor color=getColorRGB(RGB);
  updateColor(color);
}

void ColorProcessor::updateColorCMYK(QString CMYK){
  if( !checkColorText(CMYK, 4) ) return;
  if( !checkValueCMYK(CMYK) ) return;

  QColor color=getColorCMYK(CMYK);
  updateColor(color);
}

void ColorProcessor::updateColorHex(QString Hex){
  if( !checkValueHex(Hex) ) return;

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

  int val=text.toInt(&ok, 16);
  if(!ok) return QString();
  
  return text;
}
