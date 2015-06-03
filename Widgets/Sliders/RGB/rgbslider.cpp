#include "rgbslider.h"

#include <QPainter>
#include <QDebug>
#include <QtCore>


// ---------------------------------------------- consts ----------------------------------------------

const int maxRGB=255;


// ----------------------------------------------------------------------------------------------------

RGBSlider::RGBSlider(QWidget *parent) : ColorSlider(parent)
{
  sliderType=Red;
  
  r=maxF;
  g=0;
  b=0;
  
  color.setRgbF(r, g, b);
}

void RGBSlider::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  qreal val;
  switch(sliderType){
    case Red:
      val=r;
      break;
    case Green:
      val=g;
      break;
    case Blue:
      val=b;
      break;
  }
  calcVars(val);

  if(!sliderDrawn || widthChanged){
    paintComponent();
  }
  p.drawPixmap(sliderX, sliderY, sliderPixmap);

  drawPointer(p);
  drawBorder(p);
}

void RGBSlider::paintComponent(){
  sliderPixmap=QPixmap(sliderW, sliderH);
  QPainter tempP( &sliderPixmap );

  QPointF p1( sliderX, sliderH/2 );
  QPointF p2( sliderX+sliderW, sliderH/2 );
  QLinearGradient grad(p1, p2);
  
  switch(sliderType){
    case Red:
      paintRed(grad);
      break;
    case Green:
      paintGreen(grad);
      break;
    case Blue:
      paintBlue(grad);
      break;
  }
  
  tempP.setPen(Qt::NoPen);
  tempP.setBrush( QBrush(grad) );
  tempP.drawRect(0, 0, sliderW, sliderH);

  sliderDrawn=true;
  widthChanged=false;
}

void RGBSlider::paintRed(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromRgbF(0, g, b) );
  grad.setColorAt( 1, QColor::fromRgbF(1, g, b) );
}

void RGBSlider::paintGreen(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromRgbF(r, 0, b) );
  grad.setColorAt( 1, QColor::fromRgbF(r, 1, b) );
}

void RGBSlider::paintBlue(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromRgbF(r, g, 0) );
  grad.setColorAt( 1, QColor::fromRgbF(r, g, 1) );
}

void RGBSlider::updateColor(){
  ColorSlider::updateColor();

  qreal val;
  val = normalizeVal( sliderVal );
  val = qMax(0.0, val);
  val = qMin(maxF, val);
  
  switch(sliderType){
    case Red:
      r=val;
      color.setRgbF(r, g, b);
      emit redChanged(color);
      break;
    case Green:
      g=val;
      color.setRgbF(r, g, b);
      emit greenChanged(color);
      break;
    case Blue:
      b=val;
      color.setRgbF(r, g, b);
      emit blueChanged(color);
      break;
  }
}

// ---------------------------------------------- set/get ----------------------------------------------

void RGBSlider::setColorComponent(QColor color, SliderType stype) {
  if(this->color == color){
    return;
  }
  
  qreal val;
  switch(stype){
    case Red:
      r=color.redF();
      val=r;
      break;
    case Green:
      g=color.greenF();
      val=g;
      break;
    case Blue:
      b=color.blueF();
      val=b;
      break;
  }
  
  sliderVal=qCeil( val * maxRange );
  this->color=QColor::fromRgbF(r, g, b);
  update();
}

void RGBSlider::setR(QColor color) {
  setColorComponent(color, Red);
}

void RGBSlider::setG(QColor color) {
  setColorComponent(color, Green);
}

void RGBSlider::setB(QColor color) {
  setColorComponent(color, Blue);
}

// ---------------------------------------------- slots ----------------------------------------------

void RGBSlider::updateSlider() {
  this->color=QColor::fromRgbF(r, g, b);
  sliderDrawn=false;
  update();
}

void RGBSlider::changeRed(QColor color) {
  r=color.redF();
  updateSlider();
}

void RGBSlider::changeGreen(QColor color) {
  g=color.greenF();
  updateSlider();
}

void RGBSlider::changeBlue(QColor color) {
  b=color.blueF();
  updateSlider();
}

// ---------------------------------------------- service ----------------------------------------------

void RGBSlider::init(){
  if(sliderType==Red){
    sliderVal=maxRGB;
  }
}

void RGBSlider::setType(SliderType type){
  sliderType=type;
}
