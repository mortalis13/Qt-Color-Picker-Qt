#include "hsvslider.h"

#include <QPainter>
#include <QDebug>
#include <QtCore>


// ---------------------------------------------- consts ----------------------------------------------

const int maxH=360;
const int maxSV=255;
const qreal maxF=1.0;
const qreal maxHF=1.0;
const qreal maxSVF=1.0;

const qreal ratio=1.0/maxH;


// ----------------------------------------------------------------------------------------------------

HSVSlider::HSVSlider(QWidget *parent) : ColorSlider(parent)
{
  h=0;
  s=maxSVF;
  v=maxSVF;
  
  sliderType=Hue;
  
  color.setHsvF(h, s, v);
}

void HSVSlider::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  calcVars();

  if(!sliderDrawn || widthChanged){
    sliderPixmap=QPixmap(sliderW, sliderH);
    QPainter tempP( &sliderPixmap );

    QPointF p1( sliderX, sliderH/2 );
    QPointF p2( sliderX+sliderW, sliderH/2 );
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
  p.drawPixmap(sliderX, sliderY, sliderPixmap);

  drawPointer(p);
  drawBorder(p);
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
  sliderVal = pointerX - minPointerX;
  sliderVal = qMax(0, sliderVal);
  sliderVal = qMin(maxRange, sliderVal);
  
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

void HSVSlider::setH(QColor color) {
  if(this->color.hue() == color.hue()) return;
  
  h=color.hueF();
  this->color=QColor::fromHsvF(h, s, v);
  
  sliderVal=qCeil( h * maxRange );
  update();
}

void HSVSlider::setS(QColor color) {
  if(this->color==color) return;
  
  s=color.saturationF();
  this->color=QColor::fromHsvF(h, s, v);
  
  sliderVal=qCeil( s*maxRange );
  update();
}

void HSVSlider::setV(QColor color) {
  if(this->color==color) return;
  
  v=color.valueF();
  this->color=QColor::fromHsvF(h, s, v);
  
  sliderVal=qCeil( v*maxRange );
  update();
}

// ---------------------------------------------- slots ----------------------------------------------

void HSVSlider::changeHue(QColor color) {
  sliderDrawn=false;
  h=color.hueF();
  
  this->color=QColor::fromHsvF(h, s, v);
  update();
}

void HSVSlider::changeSaturation(QColor color) {
  sliderDrawn=false;
  s=color.saturationF();
  
  this->color=QColor::fromHsvF(h, s, v);
  update();
}

void HSVSlider::changeValue(QColor color) {
  sliderDrawn=false;
  v=color.valueF();
  
  this->color=QColor::fromHsvF(h, s, v);
  update();
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
