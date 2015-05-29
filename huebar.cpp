#include "huebar.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

HueBar::HueBar(QWidget *parent) : QWidget(parent)
{
  max=255;
  maxH=360;

  h=0;
  s=max;
  v=max;
}

void HueBar::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  QColor color;

  int width=this->width();

  for(int h=0; h<=maxH; ++h){
    color.setHsv(h, s, v);
    p.setPen(color);
    p.drawLine(0, h, width, h);
  }
}

void HueBar::mousePressEvent(QMouseEvent *e)
{
  updateColor(e);
}

void HueBar::mouseMoveEvent(QMouseEvent *e)
{
  updateColor(e);
}

void HueBar::updateColor(QMouseEvent* e){
  QColor color;

  h=e->y();
  if(h<0 || h>maxH) return;

  color.setHsv(h, s, v);
  emit hueChanged(color);

//  qDebug() << QString("Coordinates: %1, %2").arg(e->x()).arg(e->y());
}
