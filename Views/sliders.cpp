#include "sliders.h"
#include "ui_sliders.h"

#include <QDebug>
#include <QShortcut>


Sliders::Sliders(SlidersController *slidersController, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Sliders)
{
  ui->setupUi(this);
  
  this->slidersController=slidersController;

  addActions();
  addKeyActions();
  addShortcuts();
  init();
}

Sliders::~Sliders()
{
  delete ui;
}

void Sliders::init(){
  // setAttribute(Qt::WA_DeleteOnClose);
  
  ui->hSlider->setType(HSVSlider::Hue);
  ui->sSlider->setType(HSVSlider::Saturation);
  ui->vSlider->setType(HSVSlider::Value);
  
  ui->sSlider->init();
  ui->vSlider->init();
  
  
  ui->rSlider->setType(RGBSlider::Red);
  ui->gSlider->setType(RGBSlider::Green);
  ui->bSlider->setType(RGBSlider::Blue);
  
  ui->rSlider->init();
  
  
  ui->cSlider->setType(CMYKSlider::Cyan);
  ui->mSlider->setType(CMYKSlider::Magenta);
  ui->ySlider->setType(CMYKSlider::Yellow);
  ui->kSlider->setType(CMYKSlider::Black);
  
  ui->mSlider->init();
  ui->ySlider->init();
}

void Sliders::addActions(){
  connect( ui->hSlider, SIGNAL(hueChanged(QColor)), slidersController, SLOT(changeHue(QColor)) );
  connect( ui->sSlider, SIGNAL(saturationChanged(QColor)), slidersController, SLOT(changeSaturation(QColor)) );
  connect( ui->vSlider, SIGNAL(valueChanged(QColor)), slidersController, SLOT(changeValue(QColor)) );
  
  connect( ui->rSlider, SIGNAL(redChanged(QColor)), slidersController, SLOT(changeRed(QColor)) );
  connect( ui->gSlider, SIGNAL(greenChanged(QColor)), slidersController, SLOT(changeGreen(QColor)) );
  connect( ui->bSlider, SIGNAL(blueChanged(QColor)), slidersController, SLOT(changeBlue(QColor)) );

  connect( ui->cSlider, SIGNAL(cyanChanged(QColor)), slidersController, SLOT(changeCyan(QColor)) );
  connect( ui->mSlider, SIGNAL(magentaChanged(QColor)), slidersController, SLOT(changeMagenta(QColor)) );
  connect( ui->ySlider, SIGNAL(yellowChanged(QColor)), slidersController, SLOT(changeYellow(QColor)) );
  connect( ui->kSlider, SIGNAL(blackChanged(QColor)), slidersController, SLOT(changeBlack(QColor)) );


  connect( ui->spHue, SIGNAL(valueChanged(int)), slidersController, SLOT(changeHue(int)) );
  connect( ui->spSaturation, SIGNAL(valueChanged(int)), slidersController, SLOT(changeSaturation(int)) );
  connect( ui->spValue, SIGNAL(valueChanged(int)), slidersController, SLOT(changeValue(int)) );
  
  connect( ui->spRed, SIGNAL(valueChanged(int)), slidersController, SLOT(changeRed(int)) );
  connect( ui->spGreen, SIGNAL(valueChanged(int)), slidersController, SLOT(changeGreen(int)) );
  connect( ui->spBlue, SIGNAL(valueChanged(int)), slidersController, SLOT(changeBlue(int)) );
  
  connect( ui->spCyan, SIGNAL(valueChanged(int)), slidersController, SLOT(changeCyan(int)) );
  connect( ui->spMagenta, SIGNAL(valueChanged(int)), slidersController, SLOT(changeMagenta(int)) );
  connect( ui->spYellow, SIGNAL(valueChanged(int)), slidersController, SLOT(changeYellow(int)) );
  connect( ui->spBlack, SIGNAL(valueChanged(int)), slidersController, SLOT(changeBlack(int)) );
}

void Sliders::addKeyActions(){
  connect( ui->hSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->sSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->vSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  
  connect( ui->rSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->gSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->bSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );

  connect( ui->cSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->mSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->ySlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  connect( ui->kSlider, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(sliderMiddlePressed(QMouseEvent*)) );
  
  
  connect( this, SIGNAL(ctrlPressed()), ui->hSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->hSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->sSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->sSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->vSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->vSlider, SLOT(ctrlReleased()) );
  
  connect( this, SIGNAL(ctrlPressed()), ui->rSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->rSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->gSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->gSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->bSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->bSlider, SLOT(ctrlReleased()) );
  
  connect( this, SIGNAL(ctrlPressed()), ui->cSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->cSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->mSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->mSlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->ySlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->ySlider, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->kSlider, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->kSlider, SLOT(ctrlReleased()) );
}

void Sliders::addShortcuts(){
  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}


// --------------------------------------------- slots ---------------------------------------------

void Sliders::sliderMiddlePressed(QMouseEvent* e){
  mouseDown=true;
  mouseMoved=false;

  mx=e->x();
  my=e->y();
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
