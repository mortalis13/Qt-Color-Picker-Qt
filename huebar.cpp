#include "huebar.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

HueBar::HueBar(QWidget *parent) : QWidget(parent)
{
  max=255;
  maxH=360;
  barWidth=40;

  h=0;
  s=max;
  v=max;
}

void HueBar::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
{
  QPen pen;
  pen.setWidth(borderSize);
  pen.setColor(borderColor);

  p.setRenderHint(QPainter::Antialiasing);
  p.setPen(pen);

  QRectF rect(sizeRect.x() + borderSize/2, sizeRect.y() + borderSize/2,
              sizeRect.width() - borderSize, sizeRect.height() - borderSize);

  if(borderSize % 2 == 0)
    p.drawRoundedRect(rect, borderSize, borderSize);
  else
    p.drawRoundedRect(rect.translated(0.5, 0.5), borderRadius, borderRadius);
}

void HueBar::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  QColor color;

  int border=2;
  QColor borderColor;
  borderColor.setRgb(80,80,80,200);

  QRectF rectangle(0, 0, width(), height());
  drawRoundRect(p, rectangle, border, 10, borderColor);
  
  int x=(width() - barWidth)/2;
  for(int h=0; h<=maxH; ++h){
    int y=h+border;
    color.setHsv(h, s, v);
    p.setPen(color);
    p.drawLine(x, y, width()-x, y);
  }
}

void HueBar::mousePressEvent(QMouseEvent *e)
{
  qDebug() << QString("%1, %2").arg(rect().x()).arg(rect().y());

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

QSize HueBar::sizeHint() const
{
  return QSize( 60, 365 );
}
