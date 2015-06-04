#include "sliderscontroller.h"
#include "ui_sliders.h"

// ------------------------------------------------------------------------------------------------

SlidersController::SlidersController(QObject* parent) : QObject(parent)
{
  addActions();
  init();
}

void SlidersController::init(){
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
}

void SlidersController::addActions(){
  connectRGB();
  connectCMYK();
}

void SlidersController::setView(Sliders* slidersView){
  this->slidersView=slidersView;
}


void SlidersController::connectRGB(){
  connect( this, SIGNAL(RGBChanged(QColor)), this, SLOT(changeRedFromSelector(QColor)) );
  connect( this, SIGNAL(RGBChanged(QColor)), this, SLOT(changeGreenFromSelector(QColor)) );
  connect( this, SIGNAL(RGBChanged(QColor)), this, SLOT(changeBlueFromSelector(QColor)) );
}

void SlidersController::disconnectRGB(){
  disconnect( this, SIGNAL(RGBChanged(QColor)), 0, 0 );
}

void SlidersController::connectCMYK(){
  connect( this, SIGNAL(CMYKChanged(QColor)), this, SLOT(changeCyanFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), this, SLOT(changeMagentaFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), this, SLOT(changeYellowFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), this, SLOT(changeBlackFromSelector(QColor)) );
}

void SlidersController::disconnectCMYK(){
  disconnect( this, SIGNAL(CMYKChanged(QColor)), 0, 0 );
}


// --------------------------------------------- HSV ---------------------------------------------

// ===== hue =====

void SlidersController::changeHue(int h){
  if(hueSpinManualEdit){
    QColor filter=QColor::fromHsv(h, 0, 0);
    changeHue(filter);
  }
  hueSpinManualEdit=true;
}

void SlidersController::changeHue(QColor color){
  emit hueChanged(color);
}

void SlidersController::changeHueFromSelector(QColor color){
  hueSpinManualEdit=false;

  slidersView->ui->hSlider->setH(color);
  slidersView->ui->spHue->setValue(color.hue());
  
  slidersView->ui->sSlider->changeHue(color);
  slidersView->ui->vSlider->changeHue(color);
}

// ===== saturation =====

void SlidersController::changeSaturation(int s){
  if(saturationSpinManualEdit){
    QColor filter=QColor::fromHsv(0, s, 0);
    changeSaturation(filter);
  }
  saturationSpinManualEdit=true;
}

void SlidersController::changeSaturation(QColor color){
  emit saturationChanged(color);
}

void SlidersController::changeSaturationFromSelector(QColor color){
  saturationSpinManualEdit=false;
  
  slidersView->ui->sSlider->setS(color);
  slidersView->ui->spSaturation->setValue(color.saturation());
  
  slidersView->ui->hSlider->changeSaturation(color);
  slidersView->ui->vSlider->changeSaturation(color);
}

// ===== value =====

void SlidersController::changeValue(int v){
  if(valueSpinManualEdit){
    QColor filter=QColor::fromHsv(0, 0, v);
    changeValue(filter);
  }
  valueSpinManualEdit=true;
}

void SlidersController::changeValue(QColor color){
  emit valueChanged(color);
}

void SlidersController::changeValueFromSelector(QColor color){
  valueSpinManualEdit=false;
  
  slidersView->ui->vSlider->setV(color);
  slidersView->ui->spValue->setValue(color.value());
  
  slidersView->ui->hSlider->changeValue(color);
  slidersView->ui->sSlider->changeValue(color);
}


// --------------------------------------------- RGB ---------------------------------------------

// ===== red =====

void SlidersController::changeRed(int r){
  if(redSpinManualEdit){
    QColor filter(r, 0, 0);
    changeRed(filter);
  }
  redSpinManualEdit=true;
}

void SlidersController::changeRed(QColor color){
  emit redChanged(color);
  updateRedValues(color);
}

void SlidersController::changeRedFromSelector(QColor color){
  updateRedValues(color);
}

void SlidersController::updateRedValues(QColor color){
  slidersView->ui->rSlider->setR(color);
  
  redSpinManualEdit=false;
  slidersView->ui->spRed->setValue(color.red());
  
  slidersView->ui->gSlider->changeRed(color);
  slidersView->ui->bSlider->changeRed(color);
}

// ===== green =====

void SlidersController::changeGreen(int g){
  if(greenSpinManualEdit){
    QColor filter(0, g, 0);
    changeGreen(filter);
  }
  greenSpinManualEdit=true;
}

void SlidersController::changeGreen(QColor color){
  emit greenChanged(color);
  updateGreenValues(color);
}

void SlidersController::changeGreenFromSelector(QColor color){
  updateGreenValues(color);
}

void SlidersController::updateGreenValues(QColor color){
  slidersView->ui->gSlider->setG(color);

  greenSpinManualEdit=false;
  slidersView->ui->spGreen->setValue(color.green());

  slidersView->ui->rSlider->changeGreen(color);
  slidersView->ui->bSlider->changeGreen(color);
}

// ===== blue =====

void SlidersController::changeBlue(int b){
  if(blueSpinManualEdit){
    QColor filter(0, 0, b);
    changeBlue(filter);
  }
  blueSpinManualEdit=true;
}

void SlidersController::changeBlue(QColor color){
  emit blueChanged(color);
  updateBlueValues(color);
}

void SlidersController::changeBlueFromSelector(QColor color){
  updateBlueValues(color);
}

void SlidersController::updateBlueValues(QColor color){
  slidersView->ui->bSlider->setB(color);
  
  blueSpinManualEdit=false;
  slidersView->ui->spBlue->setValue(color.blue());
  
  slidersView->ui->rSlider->changeBlue(color);
  slidersView->ui->gSlider->changeBlue(color);
}


// --------------------------------------------- CMYK ---------------------------------------------

// ===== cyan =====

void SlidersController::changeCyan(int c){
  if(cyanSpinManualEdit){
    QColor filter=QColor::fromCmyk(c, 0, 0, 0);
    changeCyan(filter);
  }
  cyanSpinManualEdit=true;
}

void SlidersController::changeCyan(QColor color){
  emit cyanChanged(color);
  updateCyanValues(color);
}

void SlidersController::changeCyanFromSelector(QColor color){
  updateCyanValues(color);
}

void SlidersController::updateCyanValues(QColor color){
  slidersView->ui->cSlider->setC(color);
  
  cyanSpinManualEdit=false;
  slidersView->ui->spCyan->setValue(color.cyan());
  
  slidersView->ui->ySlider->changeCyan(color);
  slidersView->ui->mSlider->changeCyan(color);
  slidersView->ui->kSlider->changeCyan(color);
}

// ===== magenta =====

void SlidersController::changeMagenta(int m){
  if(magentaSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, m, 0, 0);
    changeMagenta(filter);
  }
  magentaSpinManualEdit=true;
}

void SlidersController::changeMagenta(QColor color){
  emit magentaChanged(color);
  updateMagentaValues(color);
}

void SlidersController::changeMagentaFromSelector(QColor color){
  updateMagentaValues(color);
}

void SlidersController::updateMagentaValues(QColor color){
  slidersView->ui->mSlider->setM(color);
  
  magentaSpinManualEdit=false;
  slidersView->ui->spMagenta->setValue(color.magenta());
  
  slidersView->ui->cSlider->changeMagenta(color);
  slidersView->ui->ySlider->changeMagenta(color);
  slidersView->ui->kSlider->changeMagenta(color);
}

// ===== yellow =====

void SlidersController::changeYellow(int y){
  if(yellowSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, y, 0);
    changeYellow(filter);
  }
  yellowSpinManualEdit=true;
}

void SlidersController::changeYellow(QColor color){
  emit yellowChanged(color);
  updateYellowValues(color);
}

void SlidersController::changeYellowFromSelector(QColor color){
  updateYellowValues(color);
}

void SlidersController::updateYellowValues(QColor color){
  slidersView->ui->ySlider->setY(color);
  
  yellowSpinManualEdit=false;
  slidersView->ui->spYellow->setValue(color.yellow());
  
  slidersView->ui->cSlider->changeYellow(color);
  slidersView->ui->mSlider->changeYellow(color);
  slidersView->ui->kSlider->changeYellow(color);
}

// ===== black =====

void SlidersController::changeBlack(int k){
  if(blackSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, 0, k);
    changeBlack(filter);
  }
  blackSpinManualEdit=true;
}

void SlidersController::changeBlack(QColor color){
  emit blackChanged(color);
  updateBlackValues(color);
}

void SlidersController::changeBlackFromSelector(QColor color){
  updateBlackValues(color);
}

void SlidersController::updateBlackValues(QColor color){
  slidersView->ui->kSlider->setK(color);
  
  blackSpinManualEdit=false;
  slidersView->ui->spBlack->setValue(color.black());
  
  slidersView->ui->cSlider->changeBlack(color);
  slidersView->ui->mSlider->changeBlack(color);
  slidersView->ui->ySlider->changeBlack(color);
}
