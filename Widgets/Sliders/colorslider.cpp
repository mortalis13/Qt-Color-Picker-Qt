#include "colorslider.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLinearGradient>

#include <QtCore>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int border=2;
const int borderRadius=10;

const int sliderX=border;
const int sliderY=border;

const int pointerR=5;
const int pointerBorder=2;

const QColor borderColor(80,80,80,200);

const QColor pointerColor("#333");
const QColor pointerLineColor(80,80,80,200);
const QColor pointerBorderColor("#ddd");
const QColor pointerFillColor("#333");


// ----------------------------------------------------------------------------------------------------

ColorSlider::ColorSlider(QWidget *parent) :
  QWidget(parent)
{
  sliderDrawn=false;
  middlePresed=false;
  ctrlHeld=false;
  widthChanged=false;
  
  pointerX=0;
  pointerY=0;
  
  sliderVal=0;
}

void ColorSlider::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    e->ignore();
  }
  else{
    middlePresed=false;
    movePointer( e->x() );
    updateColor();
  }
}

void ColorSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void ColorSlider::mouseReleaseEvent(QMouseEvent *e)
{
  e->ignore();
}

void ColorSlider::wheelEvent(QWheelEvent *e)
{
  QPoint p=e->angleDelta();
  
  int val=1;
  if(ctrlHeld) val=10;
  
  if(p.y()>0) incPointer(val);
  if(p.y()<0) decPointer(val);

  updateColor();
  e->accept();
}


// ---------------------------------------------- service ----------------------------------------------

void ColorSlider::calcVars(qreal val){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    sliderVal=normalizePointerX(val);
  }
  prevSliderW=sliderW;
}


void ColorSlider::movePointer(int x){
  pointerX=x;
  update();
}

void ColorSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void ColorSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void ColorSlider::decPointer(int val){
  movePointer(pointerX-val);
}


void ColorSlider::drawPointer(QPainter& p){
  correctPointer();

  pointerY = height()/2;

  QPen pen(pointerBorderColor, pointerBorder);
  p.setPen(pen);
  p.setBrush(pointerFillColor);
  p.drawEllipse( QPoint(pointerX, pointerY), pointerR, pointerR );

  pen.setColor(pointerLineColor);
  pen.setCapStyle(Qt::FlatCap);
  p.setPen(pen);

  p.drawLine( QPoint(pointerX, sliderY), QPoint(pointerX, pointerY-pointerR-pointerBorder/2) );
  p.drawLine( QPoint(pointerX, sliderY+sliderH), QPoint(pointerX, pointerY+pointerR+pointerBorder/2) );
}

void ColorSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


void ColorSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);
}


// ---------------------------------------------- correction ----------------------------------------------

qreal ColorSlider::normalizeVal(int val){
  qreal h = (qreal)val/maxRange;
  return h;
}

int ColorSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}


// ---------------------------------------------- slots ----------------------------------------------

void ColorSlider::ctrlPressed(){
  ctrlHeld=true;
}
void ColorSlider::ctrlReleased(){
  ctrlHeld=false;
}


// ---------------------------------------------- other ----------------------------------------------

void ColorSlider::updatePaint(){
  update();
}

void ColorSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void ColorSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
