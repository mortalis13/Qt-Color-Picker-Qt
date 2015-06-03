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
  redSpinManualEdit=true;
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

// ===== hue =====

void Sliders::changeHue(int h){
  emit hueChanged(h);
}

void Sliders::changeHue(QColor color){
  emit hueChanged(color);
}

void Sliders::changeHueFromSelector(QColor color){
  ui->hSlider->setH(color);
  ui->spHue->setValue(color.hue());
  
  ui->sSlider->changeHue(color);
  ui->vSlider->changeHue(color);
}

// ===== saturation =====

void Sliders::changeSaturation(int s){
  emit saturationChanged(s);
}

void Sliders::changeSaturation(QColor color){
  emit saturationChanged(color);
}

void Sliders::changeSaturationFromSelector(QColor color){
  ui->sSlider->setS(color);
  ui->spSaturation->setValue(color.saturation());
  
  ui->hSlider->changeSaturation(color);
  ui->vSlider->changeSaturation(color);
}

// ===== value =====

void Sliders::changeValue(int v){
  emit valueChanged(v);
}

void Sliders::changeValue(QColor color){
  emit valueChanged(color);
}

void Sliders::changeValueFromSelector(QColor color){
  ui->vSlider->setV(color);
  ui->spValue->setValue(color.value());
  
  ui->hSlider->changeValue(color);
  ui->sSlider->changeValue(color);
}


// --------------------------------------------- RGB ---------------------------------------------

// ===== red =====

void Sliders::changeRed(int r){
  // if(redSpinManualEdit){
  //   // emit redChanged(r);
  //   redSpinManualEdit=true;
  // }
}

void Sliders::changeRed(QColor color){
  // qDebug() << "changeRed";
  emit redChanged(color);
  ui->spRed->setValue(color.red());
}

void Sliders::changeRedFromSelector(QColor color){
  redSpinManualEdit=false;
  
  QColor filter(color.red(), 0, 0);
  
  // qDebug() << "changeRedFromSelector::r:" << color.red();
  
  ui->rSlider->setR(filter);
  ui->spRed->setValue(color.red());
  
  // ui->gSlider->changeRed(color);
  // ui->bSlider->changeRed(color);
}

// ===== green =====

void Sliders::changeGreen(int g){
  emit greenChanged(g);
}

void Sliders::changeGreen(QColor color){
  emit greenChanged(color);
}

void Sliders::changeGreenFromSelector(QColor color){
  ui->gSlider->setG(color);
  ui->spGreen->setValue(color.green());
  
  ui->rSlider->changeGreen(color);
  ui->bSlider->changeGreen(color);
}

// ===== blue =====

void Sliders::changeBlue(int b){
  emit blueChanged(b);
}

void Sliders::changeBlue(QColor color){
  emit blueChanged(color);
}

void Sliders::changeBlueFromSelector(QColor color){
  ui->bSlider->setB(color);
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
