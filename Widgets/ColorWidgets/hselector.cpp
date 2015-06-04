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
  QColor color;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  barSize=height()-2*border-1;
  
  if(!selectorDrawn){
    hSelectorPixmap=QPixmap(barWidth, barSize+1);
    QPainter tempP(&hSelectorPixmap);

    for(int h=0; h<=maxH; ++h){
      color.setHsv(h, s, v);
      tempP.setPen(color);

      qreal y = h * ( (qreal) barSize/maxH );
      tempP.drawLine( QPointF(0, y), QPointF(barWidth, y) );          // for expanding size, needs rework for mapping Y to Hue
//      tempP.drawLine(0, h, barWidth, h);
    }
    
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
  QRectF rectangle( selectorX, selectorX, barWidth, barSize+1 );                               // set inner rect coordinates (the border will be outer)
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
