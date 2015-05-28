#include "huebar.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

HueBar::HueBar(QWidget *parent) :
  QWidget(parent)
{
  h=0;
  s=255;
  v=255;
}

QSize HueBar::sizeHint() const
{
//  return QSize(this->width(), this->height());
//  return QSize(30, 360);
}

void HueBar::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  QColor color;

  int width;
  int height;
  int line=0;

  int h=0;
  int s=255;
  int v=255;

  width=this->width();
  height=this->height();

  for(int i=0;i<360;i++){
    h=i;
    line=i;

    color.setHsv(h, s, v);
    p.setPen(color);
    p.drawLine(0, line, width, line);
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
  mx=e->x();
  my=e->y();

  h=my;

  if(h<0 || h>360) return;

  color.setHsv(h, s, v);
  emit colorChanged(color);

  qDebug() << QString("Coordinates: %1, %2").arg(mx).arg(my);
}
