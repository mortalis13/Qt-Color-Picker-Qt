#include "svselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxSV=255;

const int border=2;
const int borderRadius=10;

const int minPointerXY = border;
const int maxPointerXY = maxSV+border;

const int selectorSize=maxSV+1;

const int pointerR=5;
const int pointerBorder=2;

const QColor borderColor(80,80,80,200);
const QColor pointerBorderColor("#ddd");
const QColor pointerFillColor("#333");


// ----------------------------------------------------------------------------------------------------

SVSelector::SVSelector(QWidget *parent) :
  QWidget(parent)
{
  hueLayerDrawn=false;
  middlePresed=false;
  shiftHeld=false;
  
  selectorX=border;
  selectorY=border;
  
  pointerX=maxSV;
  pointerY=0;

  h=0;
  s=maxSV;
  v=maxSV;
}

void SVSelector::paintEvent(QPaintEvent *event)
{
  QColor color;
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  if(!hueLayerDrawn){
    hueLayerImage=QImage(maxSV+1, maxSV+1, QImage::Format_RGB32);
    for(int s=0; s<=maxSV; s++){
      for(int v=0; v<=maxSV; v++){
        color.setHsv(h, s, v);
        hueLayerImage.setPixel(s, maxSV-v, color.rgb());
      }
    }
    
    hueLayerDrawn=true;
  }
  p.drawImage(border, border, hueLayerImage);
  
  drawPointer(p);
  drawBorder(p);
}

void SVSelector::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    QMouseEvent* svMouseEvent=new QMouseEvent(e->type(), e->windowPos(), e->button(), e->buttons(), e->modifiers());
    emit middlePressedSignal(svMouseEvent);
  }
  else{
    middlePresed=false;
    hideCursor(e);
    movePointer( e->x(), e->y() );
    updateColor();

//    repaint();
  }
}

void SVSelector::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    hideCursor(e);
    movePointer( e->x(), e->y() );
    updateColor();

//    repaint();
  }
}

void SVSelector::mouseReleaseEvent(QMouseEvent *e)
{
  restoreCursor();
  e->ignore();
}

void SVSelector::wheelEvent(QWheelEvent *e)
{
  QPoint p=e->angleDelta();
  int y=p.y();

  if(shiftHeld){
    if(y>0) incPointerX();
    if(y<0) decPointerX();
  }
  else{
    if(y<0) incPointerY();
    if(y>0) decPointerY();
  }

  updateColor();
  e->accept();
}


// ---------------------------------------------- service ----------------------------------------------

void SVSelector::incPointerX(){
  movePointer(pointerX+1, pointerY);
}

void SVSelector::decPointerX(){
  movePointer(pointerX-1, pointerY);
}

void SVSelector::incPointerY(){
  movePointer(pointerX, pointerY+1);
}

void SVSelector::decPointerY(){
  movePointer(pointerX, pointerY-1);
}

void SVSelector::drawPointer(QPainter& p){
  correctPointer();
  drawCircle(p);
}

void SVSelector::correctPointer(){
  pointerX = s + minPointerXY;              // to update pointer XY on text edit
  pointerY = maxPointerXY - v;
  
  pointerX = qMax( minPointerXY, pointerX );
  pointerX = qMin( maxPointerXY, pointerX );
  
  pointerY = qMax( minPointerXY, pointerY );
  pointerY = qMin( maxPointerXY, pointerY );
}

void SVSelector::movePointer(int x, int y){
  pointerX = x;
  pointerY = y;

  update();                     // if pointer doesn't move, move update() to both mousePress() and mouseMove() events
//  repaint();                  // on repaint() here it doesn't move (it repaints before the correction)
}

void SVSelector::drawBorder(QPainter& p){
  QRectF rectangle( selectorX, selectorY, selectorSize, selectorSize );
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}

void SVSelector::drawCircle(QPainter& p){
  QPen pen(pointerBorderColor, pointerBorder);
  p.setPen(pen);
  p.setBrush(pointerFillColor);
  p.drawEllipse( QPoint(pointerX, pointerY), pointerR, pointerR );
}

void SVSelector::hideCursor(QMouseEvent *e){
  int x=e->x();
  int y=e->y();

  if( ( x<minPointerXY || x>maxPointerXY ) || ( y<minPointerXY || y>maxPointerXY ) ) {
    restoreCursor();
    return;
  }
  this->setCursor( QCursor(Qt::BlankCursor) );
}

void SVSelector::restoreCursor(){
  this->setCursor( QCursor(Qt::ArrowCursor) );
}

void SVSelector::updateColor(){
  s = pointerX - border;
  v = maxSV - (pointerY - border);

  s = qMax(0, s);             // s=qMin( maxSV, qMax(0, s) );
  s = qMin(maxSV, s);

  v = qMax(0, v);
  v = qMin(maxSV, v);

  QColor color;
  color.setHsv(h, s, v);
  
  emit colorChanged(color);
  emit saturationChanged(color);
  emit valueChanged(color);
}

// ---------------------------------------------- slots ----------------------------------------------

void SVSelector::changeHue(QColor color)
{
  hueLayerDrawn=false;
  
  h=color.hue();
  correctPointer();
  
  QColor newColor;
  newColor.setHsv(h, s, v);
  emit colorChanged(newColor);

  repaint();
}

void SVSelector::shiftPressed(){
  shiftHeld=true;
}

void SVSelector::shiftReleased(){
  shiftHeld=false;
}

// ---------------------------------------------- set/get ----------------------------------------------

void SVSelector::setS(int s)
{
  if(this->s == s){
    return;
  }
  
  this->s=s;
  repaint();
  updateColor();
}

void SVSelector::setS(QColor color)
{
  s=color.saturation();
  repaint();
  updateColor();
}

void SVSelector::setV(QColor color)
{
  v=color.value();
  repaint();
  updateColor();
}

void SVSelector::setV(int v)
{
  if(this->v == v){
    return;
  }
  
  this->v=v;
  repaint();
  updateColor();
}

void SVSelector::setSV(int s, int v){
  this->s=s;
  this->v=v;
  
  repaint();
  updateColor();
}
