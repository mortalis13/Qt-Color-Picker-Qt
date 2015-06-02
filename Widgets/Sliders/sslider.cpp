#include "sslider.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLinearGradient>

#include <QtCore>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxSV=255;
const qreal maxHF=1.0;
const qreal maxSVF=1.0;

const qreal ratio=1.0/maxSV;

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

SSlider::SSlider(QWidget *parent) :
  QWidget(parent)
{
  hSliderDrawn=false;
  middlePresed=false;
  ctrlHeld=false;
  widthChanged=false;
  
  pointerX=0;
  pointerY=0;

  sliderVal=maxSV;
  
  h=0;
  s=maxSVF;
  v=maxSVF;
  
  color.setHsvF(h, s, v);
}

void SSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!hSliderDrawn || widthChanged){
    sSliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &sSliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
    QLinearGradient grad(p1, p2);

    for(qreal ss=0; ss<1.0; ss+=ratio){
      color.setHsvF(h, ss, 1);
      grad.setColorAt(ss, color);
    }

    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, sliderW, sliderH);

    hSliderDrawn=true;
    widthChanged=false;
  }
  p.drawPixmap(sliderX, sliderY, sSliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void SSlider::mousePressEvent(QMouseEvent *e)
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

void SSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void SSlider::mouseReleaseEvent(QMouseEvent *e)
{
}

void SSlider::wheelEvent(QWheelEvent *e)
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

void SSlider::calcVars(){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    int x=normalizePointerX(s);
    sliderVal=x;
  }
  prevSliderW=sliderW;
}

void SSlider::drawPointer(QPainter& p){
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

int SSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}

qreal SSlider::normalizeS(int val){
  qreal s = (qreal)val/maxRange;
  return s;
}

void SSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void SSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);

  s = normalizeS( sliderVal );
  s = qMax(0.0, s);
  s = qMin(maxSVF, s);
  
  color.setHsvF(h, s, v);
  emit saturationChanged(color);
}

void SSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void SSlider::decPointer(int val){
  movePointer(pointerX-val);
}

void SSlider::movePointer(int x){
  emit pointerMoved(x);
  pointerX=x;
  update();
}

void SSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


// ---------------------------------------------- set/get ----------------------------------------------

void SSlider::setS(QColor color)
{
  if(this->color==color){
    return;
  } 
  
  s=color.saturationF();
  sliderVal=qCeil( s*maxRange );
  
  update();
}

void SSlider::setS(qreal s)
{
  sliderVal=qCeil( s*maxRange );
  
  this->s=s;
  QColor color;
  color.setHsvF(h, s, v);

  update();
}


// ---------------------------------------------- slots ----------------------------------------------

void SSlider::ctrlPressed(){
  ctrlHeld=true;
}

void SSlider::ctrlReleased(){
  ctrlHeld=false;
}

void SSlider::changeHue(QColor color)
{
  hSliderDrawn=false;
  h=color.hueF();
  repaint();
}


// ---------------------------------------------- other ----------------------------------------------

void SSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void SSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
