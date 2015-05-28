#include "satvalueselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

SatValueSelector::SatValueSelector(QWidget *parent) :
  QWidget(parent)
{
  h=0;
  maxValue=255;
}

void SatValueSelector::changeHue(QColor color)
{
  h=color.hue();
  repaint();
}

void SatValueSelector::paintEvent(QPaintEvent *event)
{
  QPixmap pixmap(255, 255);
  QPainter p(this);
  QColor color;

  int s, v;
  int x, y;

  for(int i=maxValue;i>=0;i--){
    v=i;
    y=maxValue-i;

    for(int j=0;j<255;j++){
      s=j;
      x=j;

      color.setHsv(h, s, v);
      p.setPen(color);
      p.drawPoint(x, y);
    }
  }

//  QPainter wp(this);
//  wp.drawPixmap(0, 0, pixmap);
}

void SatValueSelector::mousePressEvent(QMouseEvent *e)
{
//  updateColor(e);
}

void SatValueSelector::mouseMoveEvent(QMouseEvent *e)
{
//  updateColor(e);
}

void SatValueSelector::updateColor(QMouseEvent* e){
  mx=e->x();
  my=e->y();

  h=my;

  if(h<0 || h>360) return;

  color.setHsv(h, s, v);
  emit colorChanged(color);

//  qDebug() << QString("Coordinates: %1, %2").arg(mx).arg(my);
}