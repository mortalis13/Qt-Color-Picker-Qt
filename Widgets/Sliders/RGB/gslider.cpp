#include "gslider.h"

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

GSlider::GSlider(QWidget *parent) :
  QWidget(parent)
{
  gSliderDrawn=false;
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

void GSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!gSliderDrawn || widthChanged){
    gSliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &gSliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
    QLinearGradient grad(p1, p2);

    grad.setColorAt( 0, QColor::fromRgbF(r, 0, b) );
    grad.setColorAt( 1, QColor::fromRgbF(r, 1, b) );

    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, sliderW, sliderH);

    gSliderDrawn=true;
    widthChanged=false;
  }
  p.drawPixmap(sliderX, sliderY, gSliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void GSlider::mousePressEvent(QMouseEvent *e)
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

void GSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void GSlider::mouseReleaseEvent(QMouseEvent *e)
{
}

void GSlider::wheelEvent(QWheelEvent *e)
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

void GSlider::calcVars(){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    int x=normalizePointerX(g);
    sliderVal=x;
  }
  prevSliderW=sliderW;
}

void GSlider::drawPointer(QPainter& p){
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

int GSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}

qreal GSlider::normalizeG(int val){
  qreal g = (qreal)val/maxRange;
  return g;
}

void GSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void GSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);

  g = normalizeG( sliderVal );
  g = qMax(0.0, g);
  g = qMin(maxF, g);
  
  color.setRgbF(r, g, b);
  emit greenChanged(color);
}

void GSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void GSlider::decPointer(int val){
  movePointer(pointerX-val);
}

void GSlider::movePointer(int x){
  emit pointerMoved(x);
  pointerX=x;
  update();
}

void GSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


// ---------------------------------------------- set/get ----------------------------------------------

void GSlider::setG(QColor color)
{
  if(this->color==color){
    return;
  } 
  
  g=color.greenF();
  this->color=QColor::fromRgbF(r, g, b);
  
  sliderVal=qCeil( g*maxRange );
  
  update();
}

void GSlider::setG(qreal g)
{
  sliderVal=qCeil( g*maxRange );
  
  this->g=g;
  QColor color;
  color.setRgbF(r, g, b);

  this->color=color;

  update();
}


// ---------------------------------------------- slots ----------------------------------------------

void GSlider::ctrlPressed(){
  ctrlHeld=true;
}

void GSlider::ctrlReleased(){
  ctrlHeld=false;
}

void GSlider::changeRed(QColor color)
{
  gSliderDrawn=false;
  r=color.redF();
  repaint();
}

void GSlider::changeBlue(QColor color)
{
  gSliderDrawn=false;
  b=color.blueF();
  repaint();
}


// ---------------------------------------------- other ----------------------------------------------

void GSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void GSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
