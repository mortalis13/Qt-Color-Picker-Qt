#include "hselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxSV=255;

const int border=2;
const int borderRadius=10;

const int barX=border;
const int barY=border;
const int barWidth=40;

const int minPointerY = border;
const int maxPointerY = maxH + minPointerY;

const int pointerWidth=10;
const int pointerDy1=1.5;
const int pointerDy2=5;

const QColor borderColor(80,80,80,200);
//const QColor borderColor("#55ffff00");
const QColor pointerColor("#333");


// ----------------------------------------------------------------------------------------------------

HSelector::HSelector(QWidget *parent) : QWidget(parent)
{
  hSelectorDrawn=false;
  middlePresed=false;

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

  barSize=height()-2*border-1;
  
  if(!hSelectorDrawn){
    hSelectorPixmap=QPixmap(barWidth, barSize+1);
    QPainter tempP(&hSelectorPixmap);

    for(int h=0; h<=maxH; ++h){
      color.setHsv(h, s, v);
      tempP.setPen(color);

      double y = h * ( (double) barSize/maxH );
      tempP.drawLine( QPointF(0, y), QPointF(barWidth, y) );          // for expanding size, needs rework for mapping Y to Hue
//      tempP.drawLine(0, h, barWidth, h);
    }
    
    hSelectorDrawn=true;
  }
  
  p.drawPixmap(barX, barY, hSelectorPixmap);

  drawPointer(p);
  drawBorder(p);
}

void HSelector::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    QMouseEvent* hMouseEvent=new QMouseEvent(e->type(), e->windowPos(), e->button(), e->buttons(), e->modifiers());
    emit middlePressedSignal(hMouseEvent);
  }
  else{
    middlePresed=false;
    movePointer(e->y());
    updateColor();
  }
}

void HSelector::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer(e->y());
    updateColor();
  }
}

void HSelector::mouseReleaseEvent(QMouseEvent *e)
{
  e->ignore();
}

void HSelector::wheelEvent(QWheelEvent *e)
{
  QPoint p=e->angleDelta();
  if(p.y()<0) incPointer();
  if(p.y()>0) decPointer();

  updateColor();
  e->accept();
}


// ---------------------------------------------- service ----------------------------------------------

void HSelector::drawPointer(QPainter& p){
  correctPointer();
//  drawRightTriangle(p);
  drawRightTrapezoid(p);
}

void HSelector::correctPointer(){
  pointerY = h + minPointerY;                       // to update pointer Y on text edit
  pointerY = qMax( minPointerY, pointerY );
  pointerY = qMin( maxPointerY, pointerY );
}

void HSelector::incPointer(){
  movePointer(pointerY+1);
}

void HSelector::decPointer(){
  movePointer(pointerY-1);
}

void HSelector::movePointer(int y){
  pointerY=y;
  update();
}

void HSelector::drawBorder(QPainter& p){
  QRectF rectangle( barX, barY, barWidth, barSize+1 );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}

void HSelector::drawRightTrapezoid(QPainter& p){
  QPen pen(Qt::NoPen);
  pen.setCapStyle(Qt::FlatCap);
  QBrush brush(pointerColor);
  p.setPen(pen);
  p.setBrush(brush);

  QPolygonF triangle;

//  qDebug() << "pointerY: " << pointerY;

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
