#include "sliders.h"
#include "ui_sliders.h"

#include <QDebug>

Sliders::Sliders(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Sliders)
{
  ui->setupUi(this);

  addActions();
  init();
}

Sliders::~Sliders()
{
  delete ui;
}

void Sliders::init(){
  hueSpinManualEdit=true;
  saturationSpinManualEdit=true;
  valueSpinManualEdit=true;
  
  redSpinManualEdit=true;
  greenSpinManualEdit=true;
  blueSpinManualEdit=true;
  
  ui->hSlider->setType(HSVSlider::Hue);
  ui->sSlider->setType(HSVSlider::Saturation);
  ui->vSlider->setType(HSVSlider::Value);
  
  ui->sSlider->init();
  ui->vSlider->init();
}

void Sliders::addActions(){
  connect( ui->hSlider, SIGNAL(hueChanged(QColor)), this, SLOT(changeHue(QColor)) );
  connect( ui->sSlider, SIGNAL(saturationChanged(QColor)), this, SLOT(changeSaturation(QColor)) );
  connect( ui->vSlider, SIGNAL(valueChanged(QColor)), this, SLOT(changeValue(QColor)) );
  
  connect( ui->rSlider, SIGNAL(redChanged(QColor)), this, SLOT(changeRed(QColor)) );
  connect( ui->gSlider, SIGNAL(greenChanged(QColor)), this, SLOT(changeGreen(QColor)) );
  connect( ui->bSlider, SIGNAL(blueChanged(QColor)), this, SLOT(changeBlue(QColor)) );


  connect( ui->spHue, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)) );
  connect( ui->spSaturation, SIGNAL(valueChanged(int)), this, SLOT(changeSaturation(int)) );
  connect( ui->spValue, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)) );
  
  connect( ui->spRed, SIGNAL(valueChanged(int)), this, SLOT(changeRed(int)) );
  connect( ui->spGreen, SIGNAL(valueChanged(int)), this, SLOT(changeGreen(int)) );
  connect( ui->spBlue, SIGNAL(valueChanged(int)), this, SLOT(changeBlue(int)) );
  
  
  connect( this, SIGNAL(ctrlPressed()), ui->hSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->hSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->sSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->sSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->vSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->vSlider, SLOT(ctrlReleased()) );
}

// --------------------------------------------- ----- ---------------------------------------------
// --------------------------------------------- slots ---------------------------------------------
// --------------------------------------------- ----- ---------------------------------------------


// --------------------------------------------- HSV ---------------------------------------------

void Sliders::changeHSVFromSelector(QColor color){
  ui->hSlider->changeSaturation(color);
  ui->hSlider->changeValue(color);
  
  ui->sSlider->changeHue(color);
  ui->sSlider->changeValue(color);
  
  ui->vSlider->changeHue(color);
  ui->vSlider->changeSaturation(color);
  
  ui->hSlider->setH(color);
  ui->sSlider->setS(color);
  ui->vSlider->setV(color);

  ui->hSlider->updatePaint();
  ui->sSlider->updatePaint();
  ui->vSlider->updatePaint();


  ui->spHue->setValue(color.hue());
  ui->spSaturation->setValue(color.saturation());
  ui->spValue->setValue(color.value());
}

// ===== hue =====

void Sliders::changeHue(int h){
  if(hueSpinManualEdit){
    QColor filter=QColor::fromHsv(h, 0, 0);
    changeHue(filter);
  }
  hueSpinManualEdit=true;
}

void Sliders::changeHue(QColor color){
  emit hueChanged(color);
}

void Sliders::changeHueFromSelector(QColor color){
  hueSpinManualEdit=false;
  
  ui->hSlider->setH(color);
  ui->spHue->setValue(color.hue());
  
  ui->sSlider->changeHue(color);
  ui->vSlider->changeHue(color);
}

// ===== saturation =====

void Sliders::changeSaturation(int s){
  if(saturationSpinManualEdit){
    QColor filter=QColor::fromHsv(0, s, 0);
    changeSaturation(filter);
  }
  saturationSpinManualEdit=true;
}

void Sliders::changeSaturation(QColor color){
  emit saturationChanged(color);
}

void Sliders::changeSaturationFromSelector(QColor color){
  saturationSpinManualEdit=false;
  
  ui->sSlider->setS(color);
  ui->spSaturation->setValue(color.saturation());
  
  ui->hSlider->changeSaturation(color);
  ui->vSlider->changeSaturation(color);
}

// ===== value =====

void Sliders::changeValue(int v){
  if(valueSpinManualEdit){
    QColor filter=QColor::fromHsv(0, 0, v);
    changeValue(filter);
  }
  valueSpinManualEdit=true;
}

void Sliders::changeValue(QColor color){
  emit valueChanged(color);
}

void Sliders::changeValueFromSelector(QColor color){
  valueSpinManualEdit=false;
  
  ui->vSlider->setV(color);
  ui->spValue->setValue(color.value());
  
  ui->hSlider->changeValue(color);
  ui->sSlider->changeValue(color);
}


// --------------------------------------------- RGB ---------------------------------------------

// ===== red =====

void Sliders::changeRed(int r){
  if(redSpinManualEdit){
    QColor filter(r, 0, 0);
    changeRed(filter);
  }
  redSpinManualEdit=true;
}

void Sliders::changeRed(QColor color){
  emit redChanged(color);
  updateRedValues(color);
}

void Sliders::changeRedFromSelector(QColor color){
  updateRedValues(color);
}

void Sliders::updateRedValues(QColor color){
  ui->rSlider->setR(color);
  
  redSpinManualEdit=false;
  ui->spRed->setValue(color.red());
  
  ui->gSlider->changeRed(color);
  ui->bSlider->changeRed(color);
}

// ===== green =====

void Sliders::changeGreen(int g){
  if(greenSpinManualEdit){
    QColor filter(0, g, 0);
    changeGreen(filter);
  }
  greenSpinManualEdit=true;
}

void Sliders::changeGreen(QColor color){
  emit greenChanged(color);
  updateGreenValues(color);
}

void Sliders::changeGreenFromSelector(QColor color){
  updateGreenValues(color);
}

void Sliders::updateGreenValues(QColor color){
  ui->gSlider->setG(color);

  greenSpinManualEdit=false;
  ui->spGreen->setValue(color.green());

  ui->rSlider->changeGreen(color);
  ui->bSlider->changeGreen(color);
}

// ===== blue =====

void Sliders::changeBlue(int b){
  if(blueSpinManualEdit){
    QColor filter(0, 0, b);
    changeBlue(filter);
  }
  blueSpinManualEdit=true;
}

void Sliders::changeBlue(QColor color){
  emit blueChanged(color);
  updateBlueValues(color);
}

void Sliders::changeBlueFromSelector(QColor color){
  updateBlueValues(color);
}

void Sliders::updateBlueValues(QColor color){
  ui->bSlider->setB(color);
  
  blueSpinManualEdit=false;
  ui->spBlue->setValue(color.blue());
  
  ui->rSlider->changeBlue(color);
  ui->gSlider->changeBlue(color);
}


// --------------------------------------------- events ---------------------------------------------

void Sliders::mousePressEvent(QMouseEvent *e)
{
  mouseDown=true;
  mouseMoved=false;

  mx=e->x();
  my=e->y();
}

void Sliders::mouseReleaseEvent(QMouseEvent *e)
{
  mouseDown=false;
  if(e->button()==Qt::MiddleButton && !mouseMoved) close();
}

void Sliders::mouseMoveEvent(QMouseEvent *e)
{
  if(mouseDown){
    mouseMoved=true;

//    emit mouseMovedOnWindow();

    int gx=e->globalX();
    int gy=e->globalY();

    int corrX=geometry().x()-x();
    int corrY=geometry().y()-y();

    int moveX=gx-mx-corrX;
    int moveY=gy-my-corrY;

    move(moveX, moveY);
  }
}

void Sliders::keyPressEvent(QKeyEvent *e)
{
  int key=e->key();
  if(key == Qt::Key_Control){
    emit ctrlPressed();
  }
}

void Sliders::keyReleaseEvent(QKeyEvent *e)
{
  int key=e->key();
  if(key == Qt::Key_Control){
    emit ctrlReleased();
  }
}
