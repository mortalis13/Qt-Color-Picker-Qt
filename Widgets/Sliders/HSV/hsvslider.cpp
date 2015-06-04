#include "hsvslider.h"

#include <QPainter>
#include <QDebug>
#include <QtCore>


// ---------------------------------------------- consts ----------------------------------------------

const int maxH=360;
const int maxSV=255;
const qreal ratio=1.0/maxH;


// ----------------------------------------------------------------------------------------------------

HSVSlider::HSVSlider(QWidget *parent) : ColorSlider(parent)
{
  sliderType=Hue;

  h=0;
  s=maxF;
  v=maxF;

  color.setHsvF(h, s, v);
}

void HSVSlider::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  qreal val;
  switch(sliderType){
    case Hue:
      val=h;
      break;
    case Saturation:
      val=s;
      break;
    case Value:
      val=v;
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

void HSVSlider::paintComponent(){
  sliderPixmap=QPixmap(sliderW, sliderH);
  QPainter tempP( &sliderPixmap );

  QPointF p1( sliderX, 0 );
  QPointF p2( sliderX+sliderW, 0 );
  
  QLinearGradient grad(p1, p2);
  
  switch(sliderType){
    case Hue:
      paintHue(grad);
      break;
    case Saturation:
      paintSaturation(grad);
      break;
    case Value:
      paintValue(grad);
      break;
  }
  
  tempP.setPen(Qt::NoPen);
  tempP.setBrush( QBrush(grad) );
  tempP.drawRect(0, 0, sliderW, sliderH);

  sliderDrawn=true;
  widthChanged=false;
}

void HSVSlider::paintHue(QLinearGradient &grad){
  QColor color;
  for(qreal hs=0; hs<1.0; hs+=ratio){
    color.setHsvF(hs, s, v);
    grad.setColorAt(hs, color);
  }
}

void HSVSlider::paintSaturation(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromHsvF(h, 0, v) );
  grad.setColorAt( 1, QColor::fromHsvF(h, 1, v) );
}

void HSVSlider::paintValue(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromHsvF(h, s, 0) );
  grad.setColorAt( 1, QColor::fromHsvF(h, s, 1) );
}

void HSVSlider::updateColor(){
  ColorSlider::updateColor();

  qreal val;

  val = normalizeVal( sliderVal );
  val = qMax(0.0, val);
  val = qMin(maxF, val);
  
  switch(sliderType){
    case Hue:
      h=val;
      color.setHsvF(h, s, v);
      emit hueChanged(color);
      break;
    case Saturation:
      s=val;
      color.setHsvF(h, s, v);
      emit saturationChanged(color);
      break;
    case Value:
      v=val;
      color.setHsvF(h, s, v);
      emit valueChanged(color);
      break;
  }
}

// ---------------------------------------------- set/get ----------------------------------------------

void HSVSlider::setColorComponent(QColor color, SliderType stype) {
  if(this->color == color){
    return;
  }
  
  qreal val;
  switch(stype){
    case Hue:
      h=color.hueF();
      val=h;
      break;
    case Saturation:
      s=color.saturationF();
      val=s;
      break;
    case Value:
      v=color.valueF();
      val=v;
      break;
  }
  
  sliderVal=qCeil( val * maxRange );
  this->color=QColor::fromHsvF(h, s, v);
  update();
}

void HSVSlider::setH(QColor color) {
  setColorComponent(color, Hue);
}

void HSVSlider::setS(QColor color) {
  setColorComponent(color, Saturation);
}

void HSVSlider::setV(QColor color) {
  setColorComponent(color, Value);
}

// ---------------------------------------------- slots ----------------------------------------------

void HSVSlider::updateSlider() {
  this->color=QColor::fromHsvF(h, s, v);
  sliderDrawn=false;
  update();
}
  
void HSVSlider::changeHue(QColor color) {
  h=color.hueF();
  updateSlider();
}

void HSVSlider::changeSaturation(QColor color) {
  s=color.saturationF();
  updateSlider();
}

void HSVSlider::changeValue(QColor color) {
  v=color.valueF();
  updateSlider();
}

// ---------------------------------------------- service ----------------------------------------------

void HSVSlider::init(){
  if(sliderType==Saturation || sliderType==Value){
    sliderVal=maxSV;
  }
}

void HSVSlider::setType(SliderType type){
  sliderType=type;
}
