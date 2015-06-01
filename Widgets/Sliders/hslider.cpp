#include "hslider.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QLinearGradient>

#include "Service/services.h"


// --------------------------------------------- consts ---------------------------------------------

const int maxH=360;
const int maxSV=255;

const double ratio=1.0/maxH;

const int border=2;
const int borderRadius=10;

const int sliderX=border;
const int sliderY=border;
const int barWidth=40;

// const int minPointerX=border;
// const int maxPointerX=maxH + minPointerX;

const int pointerWidth=10;
const int pointerDy1=1.5;
const int pointerDy2=5;

const QColor borderColor(80,80,80,200);
const QColor pointerColor("#333");


// ---

const int pointerR=5;
const int pointerBorder=2;

const QColor pointerBorderColor("#ddd");
const QColor pointerFillColor("#333");


// ----------------------------------------------------------------------------------------------------

HSlider::HSlider(QWidget *parent) :
  QWidget(parent)
{
  hSliderDrawn=false;
  middlePresed=false;
  
  pointerX=0;
  pointerY=0;
  
  h=0;
  s=maxSV;
  v=maxSV;
}

void HSlider::paintEvent(QPaintEvent *e)
{
  QColor color;
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  

  sliderX=border;
  sliderY=border;
  sliderW=width()-2*border;
  sliderH=height()-2*border;
  
  minPointerX = sliderX;
  maxPointerX = minPointerX + sliderW;


  QPointF p1( sliderX, sliderH/2 );
  QPointF p2( sliderX+sliderW, sliderH/2 );
  QLinearGradient grad(p1, p2);

  for(double hs=0; hs<1.0; hs+=ratio){
    color.setHsvF(hs, 1, 1);
    grad.setColorAt(hs, color);
//    qDebug() << QString("values: %1, %2").arg(hs).arg(color.hueF());
  }

  p.setPen(Qt::NoPen);
  p.setBrush( QBrush(grad) );
  p.drawRect(sliderX, sliderY, sliderW, sliderH);
  
  drawPointer(p);
  drawBorder(p);
}

void HSlider::mousePressEvent(QMouseEvent *e)
{
  if( e->button() == Qt::MiddleButton ){
    middlePresed=true;
    // QMouseEvent* hMouseEvent=new QMouseEvent(e->type(), e->windowPos(), e->button(), e->buttons(), e->modifiers());
    // emit middlePressedSignal(hMouseEvent);
  }
  else{
    middlePresed=false;
    hideCursor(e);
    movePointer( e->x() );
    updateColor();
  }
}

void HSlider::mouseMoveEvent(QMouseEvent *e)
{
  if(middlePresed){
    e->ignore();
  }
  else{
    hideCursor(e);
    movePointer( e->x() );
    updateColor();
  }
}

void HSlider::mouseReleaseEvent(QMouseEvent *e)
{
  restoreCursor();
}

void HSlider::wheelEvent(QWheelEvent *e)
{
}


// ---------------------------------------------- service ----------------------------------------------

void HSlider::drawPointer(QPainter& p){
  correctPointer();
//  drawRightTrapezoid(p);

  pointerY = height()/2;

  QPen pen(pointerBorderColor, pointerBorder);
  p.setPen(pen);
  p.setBrush(pointerFillColor);
  p.drawEllipse( QPoint(pointerX, pointerY), pointerR, pointerR );

  pen.setColor(borderColor);
  p.setPen(pen);

  p.drawLine( QPoint(pointerX, sliderY), QPoint(pointerX, pointerY-pointerR-pointerBorder) );
  p.drawLine( QPoint(pointerX, sliderY+sliderH), QPoint(pointerX, pointerY+pointerR+pointerBorder) );
}

void HSlider::correctPointer(){
  pointerX = h + minPointerX;
  pointerX = qMax( minPointerX, pointerX );
  pointerX = qMin( maxPointerX, pointerX );
}

void HSlider::incPointer(){
  movePointer(pointerX+1);
}

void HSlider::decPointer(){
  movePointer(pointerX-1);
}

void HSlider::movePointer(int x){
  pointerX=x;
  update();
}

void HSlider::drawBorder(QPainter& p){
  QRectF rectangle( sliderX, sliderY, sliderW, sliderH );                               // set inner rect coordinates (the border will be outer)
  Services::drawRoundRect( p, rectangle, border, borderRadius, borderColor );
}

void HSlider::hideCursor(QMouseEvent *e){
  int x=e->x();
  int y=e->y();

  if( ( x<minPointerX || x>maxPointerX ) || ( y<sliderY || y>sliderY+sliderH ) ) {
    restoreCursor();
    return;
  }
  this->setCursor( QCursor(Qt::BlankCursor) );
}

void HSlider::restoreCursor(){
  this->setCursor( QCursor(Qt::ArrowCursor) );
}

void HSlider::updateColor(){
   QColor color;

   h = pointerX-border;

   qDebug() << "pointerX: " << pointerX;

   h = qMax(0, h);
   h = qMin(maxH, h);

   color.setHsv(h, s, v);
  // emit hueChanged(color);
}

// ---------------------------------------------- set/get ----------------------------------------------

void HSlider::setH(int h)
{
  this->h=h;
  QColor color;
  color.setHsv(h, s, v);

  emit hueChanged(color);
  update();
}
