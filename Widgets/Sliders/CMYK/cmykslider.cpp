#include "cmykslider.h"

#include <QPainter>
#include <QDebug>
#include <QtCore>


// ---------------------------------------------- consts ----------------------------------------------

const int maxCMYK=255;


// ----------------------------------------------------------------------------------------------------

CMYKSlider::CMYKSlider(QWidget *parent) : ColorSlider(parent)
{
  sliderType=Cyan;
  
  c=0;
  m=maxF;
  y=maxF;
  k=0;
  
  color.setCmykF(c, m, y, k);
}

void CMYKSlider::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  qreal val;
  switch(sliderType){
    case Cyan:
      val=c;
      break;
    case Magenta:
      val=m;
      break;
    case Yellow:
      val=y;
      break;
    case Black:
      val=k;
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

void CMYKSlider::paintComponent(){
  sliderPixmap=QPixmap(sliderW, sliderH);
  QPainter tempP( &sliderPixmap );

  QPointF p1( sliderX, sliderH/2 );
  QPointF p2( sliderX+sliderW, sliderH/2 );
  QLinearGradient grad(p1, p2);
  
  switch(sliderType){
    case Cyan:
      paintCyan(grad);
      break;
    case Magenta:
      paintMagenta(grad);
      break;
    case Yellow:
      paintYellow(grad);
      break;
    case Black:
      paintBlack(grad);
      break;
  }
  
  tempP.setPen(Qt::NoPen);
  tempP.setBrush( QBrush(grad) );
  tempP.drawRect(0, 0, sliderW, sliderH);

  sliderDrawn=true;
  widthChanged=false;
}

void CMYKSlider::paintCyan(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromCmykF(0, m, y, k) );
  grad.setColorAt( 1, QColor::fromCmykF(1, m, y, k) );
}

void CMYKSlider::paintMagenta(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromCmykF(c, 0, y, k) );
  grad.setColorAt( 1, QColor::fromCmykF(c, 1, y, k) );
}

void CMYKSlider::paintYellow(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromCmykF(c, m, 0, k) );
  grad.setColorAt( 1, QColor::fromCmykF(c, m, 1, k) );
}

void CMYKSlider::paintBlack(QLinearGradient &grad){
  grad.setColorAt( 0, QColor::fromCmykF(c, m, y, 0) );
  grad.setColorAt( 1, QColor::fromCmykF(c, m, y, 1) );
}


void CMYKSlider::updateColor(){
  ColorSlider::updateColor();

  qreal val;
  val = normalizeVal( sliderVal );
  val = qMax(0.0, val);
  val = qMin(maxF, val);
  
  switch(sliderType){
    case Cyan:
      c=val;
      color.setCmykF(c, m, y, k);
      emit cyanChanged(color);
      break;
    case Magenta:
      m=val;
      color.setCmykF(c, m, y, k);
      emit magentaChanged(color);
      break;
    case Yellow:
      y=val;
      color.setCmykF(c, m, y, k);
      emit yellowChanged(color);
      break;
    case Black:
      k=val;
      color.setCmykF(c, m, y, k);
      emit blackChanged(color);
      break;
  }
}

// ---------------------------------------------- set/get ----------------------------------------------

void CMYKSlider::setColorComponent(QColor color, SliderType stype) {
  if(this->color == color){
    return;
  }
  
  qreal val;
  switch(stype){
    case Cyan:
      c=color.cyanF();
      val=c;
      break;
    case Magenta:
      m=color.magentaF();
      val=m;
      break;
    case Yellow:
      y=color.yellowF();
      val=y;
      break;
    case Black:
      k=color.blackF();
      val=k;
      break;
  }
  
  sliderVal=qCeil( val * maxRange );
  this->color=QColor::fromCmykF(c, m, y, k);
  update();
}

void CMYKSlider::setC(QColor color) {
  setColorComponent(color, Cyan);
}

void CMYKSlider::setM(QColor color) {
  setColorComponent(color, Magenta);
}

void CMYKSlider::setY(QColor color) {
  setColorComponent(color, Yellow);
}

void CMYKSlider::setK(QColor color) {
  setColorComponent(color, Black);
}

// ---------------------------------------------- slots ----------------------------------------------

void CMYKSlider::updateSlider() {
  this->color=QColor::fromCmykF(c, m, y, k);
  sliderDrawn=false;
  update();
}

void CMYKSlider::changeCyan(QColor color) {
  c=color.cyanF();
  updateSlider();
}

void CMYKSlider::changeMagenta(QColor color) {
  m=color.magentaF();
  updateSlider();
}

void CMYKSlider::changeYellow(QColor color) {
  y=color.yellowF();
  updateSlider();
}

void CMYKSlider::changeBlack(QColor color) {
  k=color.blackF();
  updateSlider();
}

// ---------------------------------------------- service ----------------------------------------------

void CMYKSlider::init(){
  if(sliderType==Magenta || sliderType==Yellow){
    sliderVal=maxCMYK;
  }
}

void CMYKSlider::setType(SliderType type){
  sliderType=type;
}
