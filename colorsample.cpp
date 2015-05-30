#include "colorsample.h"

#include <QPainter>
#include <QDebug>

#include "services.h"

ColorSample::ColorSample(QWidget *parent) :
  QWidget(parent)
{
  border=2;
  
//  color.setHsv(0, 0, 0);
  color.setHsv(0, 255, 255);
  
  borderColor.setRgb(80,80,80,200);
}

void ColorSample::changeColor(QColor color)
{
  this->color=color;
  update();
}

void ColorSample::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  p.setPen(Qt::NoPen);
  p.setBrush(color);
  p.drawRect(border, border, width()-2*border, height()-2*border);
  
  drawBorder(p);
}

void ColorSample::drawBorder(QPainter& p){
  QRectF rectangle(0, 0, width(), height());
  Services::drawInnerRoundRect(p, rectangle, border, 10, borderColor);
}
