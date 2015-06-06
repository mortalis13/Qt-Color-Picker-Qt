#include "colorsample.h"

#include <QPainter>
#include <QDebug>

#include "Service/services.h"


// ----------------------------------------------- consts -----------------------------------------------

const QColor defaultBorderColor=QColor(80,80,80,200);


// ----------------------------------------------------------------------------------------------------

ColorSample::ColorSample(QWidget *parent) : ColorWidget(parent)
{
  color.setHsv(0, maxSV, maxSV);
  borderColor=defaultBorderColor;
}


// --------------------------------------------- events ---------------------------------------------

void ColorSample::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  p.setPen(Qt::NoPen);
  p.setBrush(color);
  p.drawRect(border, border, width()-2*border, height()-2*border);
  
  drawBorder(p);
}

void ColorSample::mouseReleaseEvent(QMouseEvent *e)
{
  if(!mouseMoving){
    switch( e->button() ){
    case Qt::LeftButton:
      emit samplePressedLeft();
      break;
    case Qt::RightButton:
      emit samplePressedRight();
      break;
    case Qt::MiddleButton:
      emit samplePressedMiddle();
      e->accept();
      return;
    default:
      return;
    }
  }
  
  e->ignore();
  mouseMoving=false;
}

void ColorSample::enterEvent(QEvent *e)
{
  borderColor.setRgb(30,30,30,220);
  setCursor(Qt::PointingHandCursor);
  update();
}

void ColorSample::leaveEvent(QEvent *e)
{
  borderColor=defaultBorderColor;
  setCursor(Qt::ArrowCursor);
  update();
}


// --------------------------------------------- slots ---------------------------------------------

void ColorSample::mouseMovedOnWindow(){
  mouseMoving=true;
}

void ColorSample::mouseReleasedOnWindow(){
  mouseMoving=false;
}

void ColorSample::changeColor(QColor color)
{
  this->color=color;
  emit colorChanged(color);
  update();
}

void ColorSample::reupdateColor()
{
  emit colorChanged(color);
}

// --------------------------------------------- service ---------------------------------------------

void ColorSample::drawBorder(QPainter& p){
  QRectF rectangle(0, 0, width(), height());
  Services::drawInnerRoundRect(p, rectangle, border, borderRadius, borderColor);
}
