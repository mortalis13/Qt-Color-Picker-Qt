#include "hselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "Service/services.h"


// ----------------------------------------------------------------------------------------------------

HSelector::HSelector(QWidget *parent) : ColorWidget(parent) {
}

void HSelector::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  barSize=height()-2*border;
  
  if(!selectorDrawn){
    hSelectorPixmap=QPixmap(barWidth, barSize);
    QPainter tempP(&hSelectorPixmap);
    
    QPointF p1( 0, selectorY );
    QPointF p2( 0, height()-border );
    QLinearGradient grad(p1, p2);
    
    QColor color;
    for(qreal hs=0; hs<1.0; hs+=ratio){
      color.setHsvF(hs, sf, vf);
      grad.setColorAt(hs, color);
    }
    
    tempP.setPen(Qt::NoPen);
    tempP.setBrush( QBrush(grad) );
    tempP.drawRect(0, 0, barWidth, barSize);
    
    selectorDrawn=true;
  }
  p.drawPixmap(selectorX, selectorY, hSelectorPixmap);

  drawPointer(p);
  drawBorder(p);
}

void HSelector::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    e->ignore();
    
    QMouseEvent* mouseEvent=new QMouseEvent(e->type(), e->windowPos(), e->button(), e->buttons(), e->modifiers());
    emit middlePressedSignal(mouseEvent);
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
  
  int val=1;
  if(ctrlHeld) val=10;
  
  if(p.y()<0) incPointer(val);
  if(p.y()>0) decPointer(val);

  updateColor();
  e->accept();
}


// ---------------------------------------------- service ----------------------------------------------

void HSelector::drawPointer(QPainter& p){
  correctPointer();
  drawRightTrapezoid(p);
}

void HSelector::correctPointer(){
  pointerY = h + minPointerY;                       // to update pointer Y on text edit
  pointerY = qMax( minPointerY, pointerY );
  pointerY = qMin( maxPointerY, pointerY );
}

void HSelector::incPointer(int val){
  movePointer(pointerY+val);
}

void HSelector::decPointer(int val){
  movePointer(pointerY-val);
}

void HSelector::movePointer(int y){
  pointerY=y;
  update();
}

void HSelector::drawBorder(QPainter& p){
  QRectF rectangle( selectorX, selectorX, barWidth, barSize );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}

void HSelector::updateColor(){
  h = pointerY-border;
  h = qMax(0, h);
  h = qMin(maxH, h);
  
  color.setHsv(h, s, v);
  emit hueChanged(color);
}

void HSelector::reupdateColor(){
  emit hueChanged(color);
}

// ---------------------------------------------- set/get ----------------------------------------------

void HSelector::setInitH(int h){
  QColor color;
  color.setHsv(h, s, v);
  this->h=color.hue();
  emit hueChanged(color);
  update();
}

void HSelector::setH(int h)
{
  if(this->h == 360) this->h=0;
  if(this->h == h) return;

  QColor color;
  color.setHsv(h, s, v);
  setH(color);
}

void HSelector::setH(QColor color)
{
  int h=color.hue();
  if(this->h == 360) this->h=0;
  if(this->h == h){
    return;
  }
  
  this->h=color.hue();
  emit hueChanged(color);
  update();
}
