#include "colorsample.h"

#include <QPainter>
#include <QDebug>

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
  drawRoundRect(p, rectangle, border, 10, borderColor);
}

void ColorSample::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
{
  QPen pen;
  pen.setWidth(borderSize);
  pen.setColor(borderColor);
  pen.setJoinStyle(Qt::RoundJoin);

  p.setPen(pen);
  p.setBrush(Qt::NoBrush);

  QRectF rect(sizeRect.x() + borderSize/2, sizeRect.y() + borderSize/2,
              sizeRect.width() - borderSize, sizeRect.height() - borderSize);

  if(borderSize % 2 == 0)
    p.drawRoundedRect(rect, borderSize, borderSize);
  else
    p.drawRoundedRect(rect.translated(0.5, 0.5), borderRadius, borderRadius);
}
