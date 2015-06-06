#include "svselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "Service/services.h"


// ----------------------------------------------------------------------------------------------------

SVSelector::SVSelector(QWidget *parent) : ColorWidget(parent)
{
  pointerX=maxSV;
}

void SVSelector::paintEvent(QPaintEvent *event)
{
  QColor color;
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  if(!selectorDrawn){
    hueLayerImage=QImage(maxSV+1, maxSV+1, QImage::Format_RGB32);
    for(int s=0; s<=maxSV; s++){
      for(int v=0; v<=maxSV; v++){
        color.setHsv(h, s, v);
        hueLayerImage.setPixel(s, maxSV-v, color.rgb());
      }
    }
    
    selectorDrawn=true;
  }
  p.drawImage(border, border, hueLayerImage);
  
  drawPointer(p);
  drawBorder(p);
}

void SVSelector::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    e->ignore();
  }
  else{
    middlePresed=false;
    hideCursor(e);
    movePointer( e->x(), e->y() );
    updateColor();
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
  
  int val=1;
  if(ctrlHeld) val=10;

  if(shiftHeld){
    if(y>0) incPointerX(val);
    if(y<0) decPointerX(val);
  }
  else{
    if(y<0) incPointerY(val);
    if(y>0) decPointerY(val);
  }

  updateColor();
  e->accept();
}


// ---------------------------------------------- service ----------------------------------------------

void SVSelector::drawPointer(QPainter& p){
  correctPointer();
  drawCircle(p);
}

void SVSelector::incPointerX(int val){
  movePointer(pointerX+val, pointerY);
}

void SVSelector::decPointerX(int val){
  movePointer(pointerX-val, pointerY);
}

void SVSelector::incPointerY(int val){
  movePointer(pointerX, pointerY+val);
}

void SVSelector::decPointerY(int val){
  movePointer(pointerX, pointerY-val);
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

void SVSelector::updateColor(){
  s = pointerX - border;
  v = maxSV - (pointerY - border);

  s = qMax(0, s);             // s=qMin( maxSV, qMax(0, s) );
  s = qMin(maxSV, s);

  v = qMax(0, v);
  v = qMin(maxSV, v);

  color.setHsv(h, s, v);
  
  emit colorChanged(color);
  emit saturationChanged(color);
  emit valueChanged(color);
}

void SVSelector::reupdateColor()
{
  emit saturationChanged(color);
  emit valueChanged(color);
}

// ---------------------------------------------- slots ----------------------------------------------

void SVSelector::changeHue(QColor color)
{
  selectorDrawn=false;
  
  h=color.hue();
  correctPointer();
  
  QColor newColor;
  newColor.setHsv(h, s, v);
  emit colorChanged(newColor);

  update();
  // repaint();
}

// ---------------------------------------------- set/get ----------------------------------------------

void SVSelector::setS(QColor color)
{
  s=color.saturation();
  
  correctPointer();
  update();

  updateColor();
}

void SVSelector::setV(QColor color)
{
  v=color.value();
  
  correctPointer();
  update();

  updateColor();
}

void SVSelector::setSV(int s, int v){
  this->s=s;
  this->v=v;
  
  correctPointer();
  update();

  updateColor();
}
