#include "services.h"

Services::Services(QObject *parent) :
  QObject(parent)
{
}

// outer rect (specify rect with inner coordinates, the round rect will be outer)

void Services::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
{
  QPen pen;
  pen.setWidth(borderSize);
  pen.setColor(borderColor);
  pen.setJoinStyle(Qt::RoundJoin);

  p.setPen(pen);
  p.setBrush(Qt::NoBrush);

  QRectF rect(sizeRect.x() - borderSize/2, sizeRect.y() - borderSize/2,
              sizeRect.width() + borderSize, sizeRect.height() + borderSize);

  if(borderSize % 2 == 0)
    p.drawRoundedRect(rect, borderSize, borderSize);
  else
    p.drawRoundedRect(rect.translated(0.5, 0.5), borderRadius, borderRadius);
}


void Services::drawInnerRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
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


// ----------------- triangles for HueBar -----------------

// void Services::drawLeftTriangle(QPainter& p){
//   QPen pen(Qt::NoPen);
//   QBrush brush(pointerColor);
//   pen.setCapStyle(Qt::FlatCap);
//   p.setBrush(brush);
//   p.setPen(pen);

//   QPolygonF triangle;

//   QPoint p1(border+pointerWidth, pointerY);
//   QPoint p2(border, pointerY - triangleDy);
//   QPoint p3(border, pointerY + triangleDy);

//   triangle << p1 << p2 << p3;
//   QPainterPath path;
//   path.addPolygon(triangle);
//   p.drawPath(path);
// }

// void Services::drawRightTriangle(QPainter& p){
//   QPen pen(Qt::NoPen);
//   QBrush brush(pointerColor);
//   pen.setCapStyle(Qt::FlatCap);
//   p.setBrush(brush);
//   p.setPen(pen);

//   QPolygonF triangle;

//   QPoint p1(width()-border-pointerWidth, pointerY);
//   QPoint p2(width()-border, pointerY - triangleDy);
//   QPoint p3(width()-border, pointerY + triangleDy);

//   triangle << p1 << p2 << p3;
//   QPainterPath path;
//   path.addPolygon(triangle);
//   p.drawPath(path);
// }
