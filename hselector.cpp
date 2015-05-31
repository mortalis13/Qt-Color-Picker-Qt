#include "hselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxSV=255;

const int border=2;
const int borderRadius=10;

const int barX=border;
const int barY=border;
const int barWidth=40;

const int minPointerY=border;
const int maxPointerY=maxH + minPointerY;

const int pointerWidth=10;
const int pointerDy1=1.5;
const int pointerDy2=5;

const QColor borderColor(80,80,80,200);
const QColor pointerColor("#333");


// ----------------------------------------------------------------------------------------------------

HSelector::HSelector(QWidget *parent) : QWidget(parent)
{
  hSelectorDrawn=false;
  
  pointerY=0;
  
  h=0;
  s=maxSV;
  v=maxSV;
}

void HSelector::paintEvent(QPaintEvent *event)
{
  QColor color;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  if(!hSelectorDrawn){
    hSelectorPixmap=QPixmap(barWidth, maxH+1);
    QPainter tempP(&hSelectorPixmap);

    for(int h=0; h<=maxH; ++h){
      color.setHsv(h, s, v);
      tempP.setPen(color);
      tempP.drawLine(0, h, barWidth, h);
    }
    
    hSelectorDrawn=true;
  }
  
  p.drawPixmap(barX, barY, hSelectorPixmap);

  drawPointer(p);
  drawBorder(p);
}

void HSelector::mousePressEvent(QMouseEvent *e)
{
  movePointer(e);
  updateColor();
}

void HSelector::mouseMoveEvent(QMouseEvent *e)
{
  movePointer(e);
  updateColor();
}

void HSelector::mouseReleaseEvent(QMouseEvent *e)
{

}


// ---------------------------------------------- service ----------------------------------------------

void HSelector::drawPointer(QPainter& p){
  correctPointer();
//  drawRightTriangle(p);
  drawRightTrapezoid(p);
}

void HSelector::correctPointer(){
  pointerY = h + minPointerY;
  pointerY = qMax( minPointerY, pointerY );
  pointerY = qMin( maxPointerY, pointerY );
}

void HSelector::movePointer(QMouseEvent* e){
  pointerY=e->y();
  update();
}

void HSelector::drawBorder(QPainter& p){
  QRectF rectangle( barX, barY, barWidth, maxH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}

void HSelector::drawRightTrapezoid(QPainter& p){
  QPen pen(Qt::NoPen);
  pen.setCapStyle(Qt::FlatCap);
  QBrush brush(pointerColor);
  p.setPen(pen);
  p.setBrush(brush);

  QPolygonF triangle;

  QPoint p1( width() - pointerWidth, pointerY + pointerDy1 );
  QPoint p2( width() - pointerWidth, pointerY - pointerDy1 );
  QPoint p3( width(), pointerY - pointerDy2 );
  QPoint p4( width(), pointerY + pointerDy2 );

  triangle << p1 << p2 << p3 << p4;
  QPainterPath path;
  path.addPolygon(triangle);
  p.drawPath(path);
}

void HSelector::updateColor(){
  QColor color;

  h = pointerY-border;
  h = qMax(0, h);
  h = qMin(maxH, h);

  color.setHsv(h, s, v);
  emit hueChanged(color);
}

// ---------------------------------------------- set/get ----------------------------------------------

void HSelector::setH(int h)
{
  this->h=h;
  QColor color;
  color.setHsv(h, s, v);

  emit hueChanged(color);
  update();
}
