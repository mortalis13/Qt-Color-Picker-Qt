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
  
}

void Sliders::addActions(){
  connect( ui->hSlider, SIGNAL(hueChanged(QColor)), this, SLOT(changeHue(QColor)) );
  connect( ui->sSlider, SIGNAL(saturationChanged(QColor)), this, SLOT(changeSaturation(QColor)) );

  connect( ui->spHue, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)) );
  connect( ui->spSaturation, SIGNAL(valueChanged(int)), this, SLOT(changeSaturation(int)) );
  
  connect( this, SIGNAL(ctrlPressed()), ui->hSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->hSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->sSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->sSlider, SLOT(ctrlReleased()) );
}

// --------------------------------------------- slots ---------------------------------------------

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
