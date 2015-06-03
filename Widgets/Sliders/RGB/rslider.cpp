#include "rslider.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLinearGradient>

#include <QtCore>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxRGB=255;
const qreal maxHF=1.0;
const qreal maxF=1.0;

const qreal ratio=1.0/maxRGB;

const int border=2;
const int borderRadius=10;

const int sliderX=border;
const int sliderY=border;
const int barWidth=40;

const int pointerWidth=10;
const int pointerDy1=1.5;
const int pointerDy2=5;

const QColor borderColor(80,80,80,200);

const QColor pointerColor("#333");

// ---

const int pointerR=5;
const int pointerBorder=2;

const QColor pointerLineColor(80,80,80,200);
const QColor pointerBorderColor("#ddd");
const QColor pointerFillColor("#333");


// ----------------------------------------------------------------------------------------------------

RSlider::RSlider(QWidget *parent) :
  QWidget(parent)
{
  rSliderDrawn=false;
  middlePresed=false;
  ctrlHeld=false;
  widthChanged=false;
  
  pointerX=0;
  pointerY=0;

  sliderVal=maxRGB;
  
  r=maxF;
  g=0;
  b=0;
  
  color.setRgbF(r, g, b);
}

void RSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!rSliderDrawn || widthChanged){
    rSliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &rSliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
    QLinearGradient grad(p1, p2);

    for(qreal rs=0; rs<1.0; rs+=ratio){
      color.setRgbF(rs, g, b);
      grad.setColorAt(rs, color);
    }

    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, sliderW, sliderH);

    rSliderDrawn=true;
    widthChanged=false;
  }
  p.drawPixmap(sliderX, sliderY, rSliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void RSlider::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
  }
  else{
    middlePresed=false;
    movePointer( e->x() );
    updateColor();
  }
}

void RSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void RSlider::mouseReleaseEvent(QMouseEvent *e)
{
}

void RSlider::wheelEvent(QWheelEvent *e)
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

void RSlider::calcVars(){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    // int x=normalizePointerX(r);
    // sliderVal=x;
  }
  prevSliderW=sliderW;
}

void RSlider::drawPointer(QPainter& p){
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

int RSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}

qreal RSlider::normalizeR(int val){
  qreal r = (qreal)val/maxRange;
  return r;
}

void RSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void RSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);

  r = normalizeR( sliderVal );
  r = qMax(0.0, r);
  r = qMin(maxF, r);
  
  color.setRgbF(r, g, b);
  emit redChanged(color);
}

void RSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void RSlider::decPointer(int val){
  movePointer(pointerX-val);
}

void RSlider::movePointer(int x){
  pointerX=x;
  update();
}

void RSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


// ---------------------------------------------- set/get ----------------------------------------------

void RSlider::setR(QColor color)
{
  if(this->color==color){
    return;
  }
  
  r=color.redF();
  this->color=QColor::fromRgbF(r, g, b);
  sliderVal=qCeil( r*maxRange );
  
  update();
}

void RSlider::setR(qreal r)
{
  sliderVal=qCeil( r*maxRange );
  
  this->r=r;
  QColor color;
  color.setRgbF(r, g, b);

  this->color=color;

  update();
}


// ---------------------------------------------- slots ----------------------------------------------

void RSlider::ctrlPressed(){
  ctrlHeld=true;
}

void RSlider::ctrlReleased(){
  ctrlHeld=false;
}

void RSlider::changeGreen(QColor color)
{
  rSliderDrawn=false;
  g=color.greenF();
  repaint();
}

void RSlider::changeBlue(QColor color)
{
  rSliderDrawn=false;
  b=color.blueF();
  repaint();
}


// ---------------------------------------------- other ----------------------------------------------

void RSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void RSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
