#include "vslider.h"

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

VSlider::VSlider(QWidget *parent) :
  QWidget(parent)
{
  vSliderDrawn=false;
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

void VSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!vSliderDrawn || widthChanged){
    vSliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &vSliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
    QLinearGradient grad(p1, p2);

    for(qreal vs=0; vs<1.0; vs+=ratio){
      color.setHsvF(h, s, vs);
      grad.setColorAt(vs, color);
    }

    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, sliderW, sliderH);

    vSliderDrawn=true;
    widthChanged=false;
  }
  p.drawPixmap(sliderX, sliderY, vSliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void VSlider::mousePressEvent(QMouseEvent *e)
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

void VSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    movePointer( e->x() );
    updateColor();
  }
}

void VSlider::mouseReleaseEvent(QMouseEvent *e)
{
}

void VSlider::wheelEvent(QWheelEvent *e)
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

void VSlider::calcVars(){
  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;

  maxRange = sliderW - 1;
  minPointerX = sliderX;
  maxPointerX = minPointerX + maxRange;
  
  if(sliderW!=prevSliderW){
    widthChanged=true;
    int x=normalizePointerX(v);
    sliderVal=x;
  }
  prevSliderW=sliderW;
}

void VSlider::drawPointer(QPainter& p){
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

int VSlider::normalizePointerX(qreal val){
  qreal d=val*maxRange;
  return qCeil(d);
}

qreal VSlider::normalizeV(int val){
  qreal v = (qreal)val/maxRange;
  return v;
}

void VSlider::correctPointer(){
  pointerX = sliderVal + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void VSlider::updateColor(){
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);

  v = normalizeV( sliderVal );
  v = qMax(0.0, v);
  v = qMin(maxSVF, v);
  
  color.setHsvF(h, s, v);
  emit valueChanged(color);
}

void VSlider::incPointer(int val){
  movePointer(pointerX+val);
}

void VSlider::decPointer(int val){
  movePointer(pointerX-val);
}

void VSlider::movePointer(int x){
  emit pointerMoved(x);
  pointerX=x;
  update();
}

void VSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}


// ---------------------------------------------- set/get ----------------------------------------------

void VSlider::setV(QColor color)
{
  if(this->color==color){
    return;
  } 
  
  v=color.valueF();
  sliderVal=qCeil( v*maxRange );
  
  update();
}

void VSlider::setV(qreal v)
{
  sliderVal=qCeil( v*maxRange );
  
  this->v=v;
  QColor color;
  color.setHsvF(h, s, v);

  update();
}


// ---------------------------------------------- slots ----------------------------------------------

void VSlider::ctrlPressed(){
  ctrlHeld=true;
}

void VSlider::ctrlReleased(){
  ctrlHeld=false;
}

void VSlider::changeHue(QColor color)
{
  vSliderDrawn=false;
  h=color.hueF();
  repaint();
}

void VSlider::changeSaturation(QColor color)
{
  vSliderDrawn=false;
  s=color.saturationF();
  repaint();
}


// ---------------------------------------------- other ----------------------------------------------

void VSlider::log(QString format, int var){
 qDebug() << QString(format).arg(var);
}

void VSlider::log(QString format, qreal var){
 qDebug() << QString(format).arg(var);
}
