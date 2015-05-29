#include "huebar.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

HueBar::HueBar(QWidget *parent) : QWidget(parent)
{
  max=255;
  maxH=360;

  barWidth=40;
//  barX=(width() - barWidth)/2;

  border=2;

  pointerY=0;
  pointerWidth=10;

  triangleDy=3;
  pointerDy1=1.5;
  pointerDy2=5;

  borderColor.setRgb(80,80,80,200);
  pointerColor.setRgb(80,80,80,200);

  h=0;
  s=max;
  v=max;
}

void HueBar::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
{
  QPen pen;
  pen.setWidth(borderSize);
  pen.setColor(borderColor);

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
  QColor color;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

//  barX=(width() - barWidth)/2;
  barX=border;

  QRectF rectangle(barX-border, 0, barWidth+2*border, height());
  drawRoundRect(p, rectangle, border, 10, borderColor);
  
  for(int h=0; h<=maxH; ++h){
    int y=h+border;
    color.setHsv(h, s, v);
    p.setPen(color);
    p.drawLine(barX, y, barX+barWidth, y);
  }

  drawPointer(p);
}

void HueBar::drawLeftTriangle(QPainter& p){
  QPen pen(Qt::NoPen);
  QBrush brush(pointerColor);
  pen.setCapStyle(Qt::FlatCap);
  p.setBrush(brush);
  p.setPen(pen);

  QPolygonF triangle;

  QPoint p1(border+pointerWidth, pointerY);
  QPoint p2(border, pointerY - triangleDy);
  QPoint p3(border, pointerY + triangleDy);

  triangle << p1 << p2 << p3;
  QPainterPath path;
  path.addPolygon(triangle);
  p.drawPath(path);
}

void HueBar::drawRightTriangle(QPainter& p){
  QPen pen(Qt::NoPen);
  QBrush brush(pointerColor);
  pen.setCapStyle(Qt::FlatCap);
  p.setBrush(brush);
  p.setPen(pen);

  QPolygonF triangle;

  QPoint p1(width()-border-pointerWidth, pointerY);
  QPoint p2(width()-border, pointerY - triangleDy);
  QPoint p3(width()-border, pointerY + triangleDy);

  triangle << p1 << p2 << p3;
  QPainterPath path;
  path.addPolygon(triangle);
  p.drawPath(path);
}

void HueBar::drawRightTrapezoid(QPainter& p){
  QPen pen(Qt::NoPen);
  QBrush brush(pointerColor);
  pen.setCapStyle(Qt::FlatCap);
  p.setBrush(brush);
  p.setPen(pen);

  QPolygonF triangle;

  QPoint p1(width() - pointerWidth, pointerY + pointerDy1);
  QPoint p2(width() - pointerWidth, pointerY - pointerDy1);
  QPoint p3(width(), pointerY - pointerDy2);
  QPoint p4(width(), pointerY + pointerDy2);

  triangle << p1 << p2 << p3 << p4;
  QPainterPath path;
  path.addPolygon(triangle);
  p.drawPath(path);
}

void HueBar::drawPointer(QPainter& p){
//  drawRightTriangle(p);
  drawRightTrapezoid(p);
}

void HueBar::mousePressEvent(QMouseEvent *e)
{
  updateColor(e);
  movePointer(e);
}

void HueBar::mouseMoveEvent(QMouseEvent *e)
{
  updateColor(e);
  movePointer(e);
}

void HueBar::movePointer(QMouseEvent* e){
  pointerY=e->y();
  update();
}

void HueBar::updateColor(QMouseEvent* e){
  QColor color;

  h=e->y()-border;
  if(h<0 || h>maxH) return;

  color.setHsv(h, s, v);
  emit hueChanged(color);

//  qDebug() << QString("Coordinates: %1, %2").arg(e->x()).arg(e->y());
}

QSize HueBar::sizeHint() const
{
  return QSize( 60, 365 );
}

void HueBar::changePointerSize(double size)
{
  triangleDy=size;
  update();
}
