#include "bslider.h"

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

BSlider::BSlider(QWidget *parent) :
  QWidget(parent)
{
  bSliderDrawn=false;
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

void BSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!bSliderDrawn || widthChanged){
    bSliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &bSliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
    QLinearGradient grad(p1, p2);

    grad.setColorAt( 0, QColor::fromRgbF(r, g, 0) );
    grad.setColorAt( 1, QColor::fromRgbF(r, g, 1) );

    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, sliderW, sliderH);

    bSliderDrawn=true;
    widthChanged=false;
  }
  p.drawPixmap(sliderX, sliderY, bSliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void BSlider::mousePressEvent(QMouseEvent *e)
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

void BSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void BSlider::mouseReleaseEvent(QMouseEvent *e)
{
}

void BSlider::wheelEvent(QWheelEvent *e)
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

void BSlider::calcVars(){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    int x=normalizePointerX(b);
    sliderVal=x;
  }
  prevSliderW=sliderW;
}

void BSlider::drawPointer(QPainter& p){
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

int BSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}

qreal BSlider::normalizeB(int val){
  qreal b = (qreal)val/maxRange;
  return b;
}

void BSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void BSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);

  b = normalizeB( sliderVal );
  b = qMax(0.0, b);
  b = qMin(maxF, b);
  
  color.setRgbF(r, g, b);
  emit blueChanged(color);
}

void BSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void BSlider::decPointer(int val){
  movePointer(pointerX-val);
}

void BSlider::movePointer(int x){
  emit pointerMoved(x);
  pointerX=x;
  update();
}

void BSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


// ---------------------------------------------- set/get ----------------------------------------------

void BSlider::setB(QColor color)
{
  if(this->color==color){
    return;
  } 
  
  b=color.blueF();
  this->color=QColor::fromRgbF(r, g, b);
  
  sliderVal=qCeil( b*maxRange );
  
  update();
}

void BSlider::setB(qreal b)
{
  sliderVal=qCeil( b*maxRange );
  
  this->b=b;
  QColor color;
  color.setRgbF(r, g, b);

  this->color=color;

  update();
}


// ---------------------------------------------- slots ----------------------------------------------

void BSlider::ctrlPressed(){
  ctrlHeld=true;
}

void BSlider::ctrlReleased(){
  ctrlHeld=false;
}

void BSlider::changeRed(QColor color)
{
  bSliderDrawn=false;
  r=color.redF();
  repaint();
}

void BSlider::changeGreen(QColor color)
{
  bSliderDrawn=false;
  g=color.greenF();
  repaint();
}


// ---------------------------------------------- other ----------------------------------------------

void BSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void BSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
