#include "validator.h"

#include <QtCore>


// -------------------------------------------- consts --------------------------------------------

const int maxH = 359;
const int maxS = 255;
const int maxV = 255;

const int maxRGB = 255;
const int maxCMYK = 255;

const int maxHex = 255;
const int maxShortHex = 15;

// ----------------------------------------------------------------------------------------------------

Validator::Validator(QObject *parent) :
  QObject(parent)
{
}

bool Validator::checkColorText(QString text, Vars::ColorType colorType) {
  int size = getSizeByType(colorType);
  
  QStringList list;
  list = text.split(" ");
  if (list.size()!=size) return false;

  foreach(QString comp, list) {
    if (!comp.length())
      return false;
  }

  foreach(QString comp, list) {
    bool ok;
    comp.toInt(&ok);
    if (!ok) return false;
  }

  return true;
}

bool Validator::checkValueByType(QString text, Vars::ColorType colorType) {
  switch (colorType) {
    case Vars::HSV:
      return checkValueHSV(text);
    case Vars::RGB:
      return checkValueRGB(text);
    case Vars::CMYK:
      return checkValueCMYK(text);
    case Vars::Hex:
      return checkValueHex(text);
  }
  return false;
}

bool Validator::checkValueHSV(QString text) {
  QStringList list;
  list = text.split(" ");

  int h = list[0].toInt();
  int s = list[1].toInt();
  int v = list[2].toInt();

  if (h<0 || h>maxH) return false;
  if (s<0 || s>maxH) return false;
  if (v<0 || v>maxH) return false;

  return true;
}

bool Validator::checkValueRGB(QString text) {
  QStringList list;
  list = text.split(" ");

  int r = list[0].toInt();
  int g = list[1].toInt();
  int b = list[2].toInt();

  if (r<0 || r>maxRGB) return false;
  if (g<0 || g>maxRGB) return false;
  if (b<0 || b>maxRGB) return false;

  return true;
}

bool Validator::checkValueCMYK(QString text) {
  QStringList list;
  list = text.split(" ");

  int c = list[0].toInt();
  int m = list[1].toInt();
  int y = list[2].toInt();
  int k = list[3].toInt();

  if (c<0 || c>maxCMYK) return false;
  if (m<0 || m>maxCMYK) return false;
  if (y<0 || y>maxCMYK) return false;
  if (k<0 || k>maxCMYK) return false;

  return true;
}

bool Validator::checkValueHex(QString text) {
  int len = text.length();
  if ( len!=6 && len!=3 ) return false;
  
  bool ok;
  int factor = len/3;

  for (int i = 0; i<3; i++) {
    QString comp = text.mid(i*factor, factor);
    int val = comp.toInt(&ok, 16);
    if (!ok) return false;

    if (len == 3) {
      if (val<0 || val>maxShortHex) return false;
    }
    else {
      if (val<0 || val>maxHex) return false;
    }
  }

  return true;
}

bool Validator::checkComponentVal(int val, Vars::ColorType colorType, int group, int hexLen) {
  if (colorType == Vars::HSV) {
    switch (group) {
    case 0:
      return (val >= 0 && val <= maxH);
    case 1:
      return (val >= 0 && val <= maxS);
    case 2:
      return (val >= 0 && val <= maxV);
    }
  }

  if (colorType == Vars::RGB) {
    return (val >= 0 && val <= maxRGB);
  }

  if (colorType == Vars::CMYK) {
    switch (group) {
    case 0:
      return (val >= 0 && val <= maxCMYK);
    case 1:
      return (val >= 0 && val <= maxCMYK);
    case 2:
      return (val >= 0 && val <= maxCMYK);
    case 3:
      return (val >= 0 && val <= maxCMYK);
    }
  }

  if (colorType == Vars::Hex) {
    if (hexLen == 3)
      return (val >= 0 && val <= maxShortHex);
    else if (hexLen == 6)
      return (val >= 0 && val <= maxHex);
  }

  return false;
}


void Validator::correctHSV(QColor& color) {
  int h = color.hue();
  int s = color.saturation();
  int v = color.value();
  
  h = qMin(maxH, qMax(0, h));
  s = qMin(maxS, qMax(0, s));
  v = qMin(maxV, qMax(0, v));
  
  color.setHsv(h, s, v);
}

void Validator::correctRGB(QColor& color) {
  int r = color.red();
  int g = color.green();
  int b = color.blue();
  
  r = qMin(maxRGB, qMax(0, r));
  g = qMin(maxRGB, qMax(0, g));
  b = qMin(maxRGB, qMax(0, b));
  
  color.setRgb(r, g, b);
}

void Validator::correctCMYK(QColor& color) {
  int c = color.cyan();
  int m = color.magenta();
  int y = color.yellow();
  int k = color.black();
  
  c = qMin(maxCMYK, qMax(0, c));
  m = qMin(maxCMYK, qMax(0, m));
  y = qMin(maxCMYK, qMax(0, y));
  k = qMin(maxCMYK, qMax(0, k));
  
  color.setCmyk(c, m, y, k);
}


QString Validator::correctColorText(QString text) {
  if (!text.length()) return text;
  return text.trimmed().replace(",", " ").replace(QRegExp("\\s+"), " ");
}


// --------------------------------------------- service ---------------------------------------------

int Validator::getSizeByType(Vars::ColorType colorType) {
  switch (colorType) {
    case Vars::HSV:
      return 3;
    case Vars::RGB:
      return 3;
    case Vars::CMYK:
      return 4;
    default:
      return 0;
  }
}
