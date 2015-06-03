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
  
  cyanSpinManualEdit=true;
  magentaSpinManualEdit=true;
  yellowSpinManualEdit=true;
  blackSpinManualEdit=true;
  
  
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
  connect( ui->hSlider, SIGNAL(hueChanged(QColor)), this, SLOT(changeHue(QColor)) );
  connect( ui->sSlider, SIGNAL(saturationChanged(QColor)), this, SLOT(changeSaturation(QColor)) );
  connect( ui->vSlider, SIGNAL(valueChanged(QColor)), this, SLOT(changeValue(QColor)) );
  
  connect( ui->rSlider, SIGNAL(redChanged(QColor)), this, SLOT(changeRed(QColor)) );
  connect( ui->gSlider, SIGNAL(greenChanged(QColor)), this, SLOT(changeGreen(QColor)) );
  connect( ui->bSlider, SIGNAL(blueChanged(QColor)), this, SLOT(changeBlue(QColor)) );

  connect( ui->cSlider, SIGNAL(cyanChanged(QColor)), this, SLOT(changeCyan(QColor)) );
  connect( ui->mSlider, SIGNAL(magentaChanged(QColor)), this, SLOT(changeMagenta(QColor)) );
  connect( ui->ySlider, SIGNAL(yellowChanged(QColor)), this, SLOT(changeYellow(QColor)) );
  connect( ui->kSlider, SIGNAL(blackChanged(QColor)), this, SLOT(changeBlack(QColor)) );


  connect( ui->spHue, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)) );
  connect( ui->spSaturation, SIGNAL(valueChanged(int)), this, SLOT(changeSaturation(int)) );
  connect( ui->spValue, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)) );
  
  connect( ui->spRed, SIGNAL(valueChanged(int)), this, SLOT(changeRed(int)) );
  connect( ui->spGreen, SIGNAL(valueChanged(int)), this, SLOT(changeGreen(int)) );
  connect( ui->spBlue, SIGNAL(valueChanged(int)), this, SLOT(changeBlue(int)) );
  
  connect( ui->spCyan, SIGNAL(valueChanged(int)), this, SLOT(changeCyan(int)) );
  connect( ui->spMagenta, SIGNAL(valueChanged(int)), this, SLOT(changeMagenta(int)) );
  connect( ui->spYellow, SIGNAL(valueChanged(int)), this, SLOT(changeYellow(int)) );
  connect( ui->spBlack, SIGNAL(valueChanged(int)), this, SLOT(changeBlack(int)) );
  
  
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


// --------------------------------------------- CMYK ---------------------------------------------

// ===== cyan =====

void Sliders::changeCyan(int c){
  if(cyanSpinManualEdit){
    QColor filter=QColor::fromCmyk(c, 0, 0, 0);
    changeCyan(filter);
  }
  cyanSpinManualEdit=true;
}

void Sliders::changeCyan(QColor color){
  emit cyanChanged(color);
  updateCyanValues(color);
}

void Sliders::changeCyanFromSelector(QColor color){
  updateCyanValues(color);
}

void Sliders::updateCyanValues(QColor color){
  ui->cSlider->setC(color);
  
  cyanSpinManualEdit=false;
  ui->spCyan->setValue(color.cyan());
  
  ui->ySlider->changeCyan(color);
  ui->mSlider->changeCyan(color);
  ui->kSlider->changeCyan(color);
}

// ===== magenta =====

void Sliders::changeMagenta(int m){
  if(magentaSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, m, 0, 0);
    changeMagenta(filter);
  }
  magentaSpinManualEdit=true;
}

void Sliders::changeMagenta(QColor color){
  emit magentaChanged(color);
  updateMagentaValues(color);
}

void Sliders::changeMagentaFromSelector(QColor color){
  updateMagentaValues(color);
}

void Sliders::updateMagentaValues(QColor color){
  ui->mSlider->setM(color);
  
  magentaSpinManualEdit=false;
  ui->spMagenta->setValue(color.magenta());
  
  ui->cSlider->changeMagenta(color);
  ui->ySlider->changeMagenta(color);
  ui->kSlider->changeMagenta(color);
}

// ===== yellow =====

void Sliders::changeYellow(int y){
  if(yellowSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, y, 0);
    changeYellow(filter);
  }
  yellowSpinManualEdit=true;
}

void Sliders::changeYellow(QColor color){
  emit yellowChanged(color);
  updateYellowValues(color);
}

void Sliders::changeYellowFromSelector(QColor color){
  updateYellowValues(color);
}

void Sliders::updateYellowValues(QColor color){
  ui->ySlider->setY(color);
  
  yellowSpinManualEdit=false;
  ui->spYellow->setValue(color.yellow());
  
  ui->cSlider->changeYellow(color);
  ui->mSlider->changeYellow(color);
  ui->kSlider->changeYellow(color);
}

// ===== black =====

void Sliders::changeBlack(int k){
  if(blackSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, 0, k);
    changeBlack(filter);
  }
  blackSpinManualEdit=true;
}

void Sliders::changeBlack(QColor color){
  emit blackChanged(color);
  updateBlackValues(color);
}

void Sliders::changeBlackFromSelector(QColor color){
  updateBlackValues(color);
}

void Sliders::updateBlackValues(QColor color){
  ui->kSlider->setK(color);
  
  blackSpinManualEdit=false;
  ui->spBlack->setValue(color.black());
  
  ui->cSlider->changeBlack(color);
  ui->mSlider->changeBlack(color);
  ui->ySlider->changeBlack(color);
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
