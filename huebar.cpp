#include "huebar.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

HueBar::HueBar(QWidget *parent) : QWidget(parent)
{
  hueBarDrawn=false;
  
  max=255;
  maxH=360;

  barWidth=40;
  border=2;

  pointerY=0;
  pointerWidth=10;

  triangleDy=3;
  pointerDy1=1.5;
  pointerDy2=5;

  borderColor.setRgb(80,80,80,200);
  pointerColor.setNamedColor("#333");

  h=0;
  s=max;
  v=max;
}

void HueBar::paintEvent(QPaintEvent *event)
{
  QColor color;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  barX=border;
  barY=border;
  
  if(!hueBarDrawn){
    hueBarPixmap=QPixmap(barWidth, maxH+1);
    QPainter tempP(&hueBarPixmap);

    for(int h=0; h<=maxH; ++h){
      color.setHsv(h, s, v);
      tempP.setPen(color);
      tempP.drawLine(0, h, barWidth, h);
    }
    
    hueBarDrawn=true;
  }
  
  p.drawPixmap(barX, barY, hueBarPixmap);

  drawPointer(p);
  drawBorder(p);
}

void HueBar::drawPointer(QPainter& p){
  correctPointer();
//  drawRightTriangle(p);
  drawRightTrapezoid(p);
}

void HueBar::drawBorder(QPainter& p){
  QRectF rectangle(barX-border, 0, barWidth+2*border, height());
  drawRoundRect(p, rectangle, border, 10, borderColor);
}

void HueBar::correctPointer(){
//  if(pointerY-border<0) pointerY=border;
//  if(pointerY-border>maxH) pointerY=maxH+border;

  pointerY=qMax(0+border, pointerY);
  pointerY=qMin(maxH+border, pointerY);
}

void HueBar::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
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

void HueBar::drawRightTrapezoid(QPainter& p){
  QPen pen(Qt::NoPen);
  pen.setCapStyle(Qt::FlatCap);
  QBrush brush(pointerColor);
  p.setPen(pen);
  p.setBrush(brush);

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

  h=qMax(0, h);
  h=qMin(maxH, h);

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
