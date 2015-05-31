#include "validator.h"

#include <QtCore>


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

Validator::Validator(QObject *parent) :
  QObject(parent)
{
}

int Validator::getSizeByType(int colorType){
  switch(colorType){
    case HSV:
      return 3;
    case RGB:
      return 3;
    case CMYK:
      return 4;
    default:
      return 0;
  }
}

bool Validator::checkColorText(QString text, int colorType){
  int size=getSizeByType(colorType);
  
  QStringList list;
  list=text.split(" ");
  if(list.size()!=size) return false;

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

bool Validator::checkValueByType(QString text, int colorType){
  switch(colorType){
    case HSV:
      return checkValueHSV(text);
    case RGB:
      return checkValueRGB(text);
    case CMYK:
      return checkValueCMYK(text);
    case Hex:
      return checkValueHex(text);
  }
}

bool Validator::checkValueHSV(QString text){
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

bool Validator::checkValueRGB(QString text){
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

bool Validator::checkValueCMYK(QString text){
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

bool Validator::checkValueHex(QString text){
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

QColor Validator::correctColor(QColor color){
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


bool Validator::checkComponentVal(int val, int colorType, int group, int hexLen){
  if(colorType==HSV){
    switch(group){
    case 0:
      return (val>=minH && val<=maxH);
      break;
    case 1:
      return (val>=minS && val<=maxS);
      break;
    case 2:
      return (val>=minV && val<=maxV);
      break;
    }
  }

  if(colorType==RGB){
    return (val>=minRGB && val<=maxRGB);
  }

  if(colorType==CMYK){
    switch(group){
    case 0:
      return (val>=minC && val<=maxC);
      break;
    case 1:
      return (val>=minM && val<=maxM);
      break;
    case 2:
      return (val>=minY && val<=maxY);
      break;
    case 3:
      return (val>=minK && val<=maxK);
      break;
    }
  }

  if(colorType==Hex){
    if(hexLen==3)
      return (val>=minSHex && val<=maxSHex);
    else if(hexLen==6)
      return (val>=minHex && val<=maxHex);
  }
}
