#include "sliderscontroller.h"
#include "ui_sliders.h"

// ------------------------------------------------------------------------------------------------

// SlidersController::SlidersController(SlidersController* slidersColorModel, QObject* parent) : QObject(parent)
SlidersController::SlidersController(QObject* parent) : QObject(parent)
{
  // this->slidersColorModel=slidersColorModel;
  
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

void SlidersController::setView(Sliders* slidersView){
  this->slidersView=slidersView;
}

void SlidersController::addActions(){
  // connect( this, SIGNAL(hueChanged(QColor)), slidersColorModel, SLOT(changeHue(QColor)) );
  // connect( this, SIGNAL(saturationChanged(QColor)), slidersColorModel, SLOT(changeSaturation(QColor)) );
  // connect( this, SIGNAL(valueChanged(QColor)), slidersColorModel, SLOT(changeValue(QColor)) );
  
  // connect( this, SIGNAL(redChanged(QColor)), slidersColorModel, SLOT(changeRed(QColor)) );
  // connect( this, SIGNAL(greenChanged(QColor)), slidersColorModel, SLOT(changeGreen(QColor)) );
  // connect( this, SIGNAL(blueChanged(QColor)), slidersColorModel, SLOT(changeBlue(QColor)) );

  // connect( this, SIGNAL(cyanChanged(QColor)), slidersColorModel, SLOT(changeCyan(QColor)) );
  // connect( this, SIGNAL(magentaChanged(QColor)), slidersColorModel, SLOT(changeMagenta(QColor)) );
  // connect( this, SIGNAL(yellowChanged(QColor)), slidersColorModel, SLOT(changeYellow(QColor)) );
  // connect( this, SIGNAL(blackChanged(QColor)), slidersColorModel, SLOT(changeBlack(QColor)) );


  // connect( this, SIGNAL(hueChanged(int)), slidersColorModel, SLOT(changeHue(int)) );
  // connect( this, SIGNAL(saturationChanged(int)), slidersColorModel, SLOT(changeSaturation(int)) );
  // connect( this, SIGNAL(valueChanged(int)), slidersColorModel, SLOT(changeValue(int)) );
  
  // connect( this, SIGNAL(redChanged(int)), slidersColorModel, SLOT(changeRed(int)) );
  // connect( this, SIGNAL(greenChanged(int)), slidersColorModel, SLOT(changeGreen(int)) );
  // connect( this, SIGNAL(blueChanged(int)), slidersColorModel, SLOT(changeBlue(int)) );
  
  // connect( this, SIGNAL(cyanChanged(int)), slidersColorModel, SLOT(changeCyan(int)) );
  // connect( this, SIGNAL(magentaChanged(int)), slidersColorModel, SLOT(changeMagenta(int)) );
  // connect( this, SIGNAL(yellowChanged(int)), slidersColorModel, SLOT(changeYellow(int)) );
  // connect( this, SIGNAL(blackChanged(int)), slidersColorModel, SLOT(changeBlack(int)) );
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

