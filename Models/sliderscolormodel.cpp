#include "sliderscolormodel.h"

#include "Service/validator.h"
#include "ui_sliders.h"


// ------------------------------------------------------------------------------------------------

SlidersColorModel::SlidersColorModel(QObject* parent) : QObject(parent)
{
  // this->slidersView=slidersView;
  
  addActions();
  init();
}

void SlidersColorModel::init(){
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

void SlidersColorModel::setView(Sliders* slidersView){
  this->slidersView=slidersView;
}

void SlidersColorModel::addActions(){
  // connect( slidersController, SIGNAL(hueChanged(QColor)), this, SLOT(changeHue(QColor)) );
  
  // connect( this, SIGNAL(saturationChanged(QColor)), this, SLOT(changeSaturation(QColor)) );
  // connect( this, SIGNAL(valueChanged(QColor)), this, SLOT(changeValue(QColor)) );
  
  // connect( this, SIGNAL(redChanged(QColor)), this, SLOT(changeRed(QColor)) );
  // connect( this, SIGNAL(greenChanged(QColor)), this, SLOT(changeGreen(QColor)) );
  // connect( this, SIGNAL(blueChanged(QColor)), this, SLOT(changeBlue(QColor)) );

  // connect( this, SIGNAL(cyanChanged(QColor)), this, SLOT(changeCyan(QColor)) );
  // connect( this, SIGNAL(magentaChanged(QColor)), this, SLOT(changeMagenta(QColor)) );
  // connect( this, SIGNAL(yellowChanged(QColor)), this, SLOT(changeYellow(QColor)) );
  // connect( this, SIGNAL(blackChanged(QColor)), this, SLOT(changeBlack(QColor)) );


  // connect( this, SIGNAL(hueChanged(int)), this, SLOT(changeHue(int)) );
  // connect( this, SIGNAL(saturationChanged(int)), this, SLOT(changeSaturation(int)) );
  // connect( this, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)) );
  
  // connect( this, SIGNAL(redChanged(int)), this, SLOT(changeRed(int)) );
  // connect( this, SIGNAL(greenChanged(int)), this, SLOT(changeGreen(int)) );
  // connect( this, SIGNAL(blueChanged(int)), this, SLOT(changeBlue(int)) );
  
  // connect( this, SIGNAL(cyanChanged(int)), this, SLOT(changeCyan(int)) );
  // connect( this, SIGNAL(magentaChanged(int)), this, SLOT(changeMagenta(int)) );
  // connect( this, SIGNAL(yellowChanged(int)), this, SLOT(changeYellow(int)) );
  // connect( this, SIGNAL(blackChanged(int)), this, SLOT(changeBlack(int)) );
}

// --------------------------------------------- HSV ---------------------------------------------

// ===== hue =====

void SlidersColorModel::changeHue(int h){
  if(hueSpinManualEdit){
    QColor filter=QColor::fromHsv(h, 0, 0);
    changeHue(filter);
  }
  hueSpinManualEdit=true;
}

void SlidersColorModel::changeHue(QColor color){
  emit hueChanged(color);
}

void SlidersColorModel::changeHueFromSelector(QColor color){
  hueSpinManualEdit=false;

  slidersView->ui->hSlider->setH(color);
  slidersView->ui->spHue->setValue(color.hue());
  
  slidersView->ui->sSlider->changeHue(color);
  slidersView->ui->vSlider->changeHue(color);
}

// ===== saturation =====

void SlidersColorModel::changeSaturation(int s){
  if(saturationSpinManualEdit){
    QColor filter=QColor::fromHsv(0, s, 0);
    changeSaturation(filter);
  }
  saturationSpinManualEdit=true;
}

void SlidersColorModel::changeSaturation(QColor color){
  emit saturationChanged(color);
}

void SlidersColorModel::changeSaturationFromSelector(QColor color){
  saturationSpinManualEdit=false;
  
  slidersView->ui->sSlider->setS(color);
  slidersView->ui->spSaturation->setValue(color.saturation());
  
  slidersView->ui->hSlider->changeSaturation(color);
  slidersView->ui->vSlider->changeSaturation(color);
}

// ===== value =====

void SlidersColorModel::changeValue(int v){
  if(valueSpinManualEdit){
    QColor filter=QColor::fromHsv(0, 0, v);
    changeValue(filter);
  }
  valueSpinManualEdit=true;
}

void SlidersColorModel::changeValue(QColor color){
  emit valueChanged(color);
}

void SlidersColorModel::changeValueFromSelector(QColor color){
  valueSpinManualEdit=false;
  
  slidersView->ui->vSlider->setV(color);
  slidersView->ui->spValue->setValue(color.value());
  
  slidersView->ui->hSlider->changeValue(color);
  slidersView->ui->sSlider->changeValue(color);
}


// --------------------------------------------- RGB ---------------------------------------------

// ===== red =====

void SlidersColorModel::changeRed(int r){
  if(redSpinManualEdit){
    QColor filter(r, 0, 0);
    changeRed(filter);
  }
  redSpinManualEdit=true;
}

void SlidersColorModel::changeRed(QColor color){
  emit redChanged(color);
  updateRedValues(color);
}

void SlidersColorModel::changeRedFromSelector(QColor color){
  updateRedValues(color);
}

void SlidersColorModel::updateRedValues(QColor color){
  slidersView->ui->rSlider->setR(color);
  
  redSpinManualEdit=false;
  slidersView->ui->spRed->setValue(color.red());
  
  slidersView->ui->gSlider->changeRed(color);
  slidersView->ui->bSlider->changeRed(color);
}

// ===== green =====

void SlidersColorModel::changeGreen(int g){
  if(greenSpinManualEdit){
    QColor filter(0, g, 0);
    changeGreen(filter);
  }
  greenSpinManualEdit=true;
}

void SlidersColorModel::changeGreen(QColor color){
  emit greenChanged(color);
  updateGreenValues(color);
}

void SlidersColorModel::changeGreenFromSelector(QColor color){
  updateGreenValues(color);
}

void SlidersColorModel::updateGreenValues(QColor color){
  slidersView->ui->gSlider->setG(color);

  greenSpinManualEdit=false;
  slidersView->ui->spGreen->setValue(color.green());

  slidersView->ui->rSlider->changeGreen(color);
  slidersView->ui->bSlider->changeGreen(color);
}

// ===== blue =====

void SlidersColorModel::changeBlue(int b){
  if(blueSpinManualEdit){
    QColor filter(0, 0, b);
    changeBlue(filter);
  }
  blueSpinManualEdit=true;
}

void SlidersColorModel::changeBlue(QColor color){
  emit blueChanged(color);
  updateBlueValues(color);
}

void SlidersColorModel::changeBlueFromSelector(QColor color){
  updateBlueValues(color);
}

void SlidersColorModel::updateBlueValues(QColor color){
  slidersView->ui->bSlider->setB(color);
  
  blueSpinManualEdit=false;
  slidersView->ui->spBlue->setValue(color.blue());
  
  slidersView->ui->rSlider->changeBlue(color);
  slidersView->ui->gSlider->changeBlue(color);
}


// --------------------------------------------- CMYK ---------------------------------------------

// ===== cyan =====

void SlidersColorModel::changeCyan(int c){
  if(cyanSpinManualEdit){
    QColor filter=QColor::fromCmyk(c, 0, 0, 0);
    changeCyan(filter);
  }
  cyanSpinManualEdit=true;
}

void SlidersColorModel::changeCyan(QColor color){
  emit cyanChanged(color);
  updateCyanValues(color);
}

void SlidersColorModel::changeCyanFromSelector(QColor color){
  updateCyanValues(color);
}

void SlidersColorModel::updateCyanValues(QColor color){
  slidersView->ui->cSlider->setC(color);
  
  cyanSpinManualEdit=false;
  slidersView->ui->spCyan->setValue(color.cyan());
  
  slidersView->ui->ySlider->changeCyan(color);
  slidersView->ui->mSlider->changeCyan(color);
  slidersView->ui->kSlider->changeCyan(color);
}

// ===== magenta =====

void SlidersColorModel::changeMagenta(int m){
  if(magentaSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, m, 0, 0);
    changeMagenta(filter);
  }
  magentaSpinManualEdit=true;
}

void SlidersColorModel::changeMagenta(QColor color){
  emit magentaChanged(color);
  updateMagentaValues(color);
}

void SlidersColorModel::changeMagentaFromSelector(QColor color){
  updateMagentaValues(color);
}

void SlidersColorModel::updateMagentaValues(QColor color){
  slidersView->ui->mSlider->setM(color);
  
  magentaSpinManualEdit=false;
  slidersView->ui->spMagenta->setValue(color.magenta());
  
  slidersView->ui->cSlider->changeMagenta(color);
  slidersView->ui->ySlider->changeMagenta(color);
  slidersView->ui->kSlider->changeMagenta(color);
}

// ===== yellow =====

void SlidersColorModel::changeYellow(int y){
  if(yellowSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, y, 0);
    changeYellow(filter);
  }
  yellowSpinManualEdit=true;
}

void SlidersColorModel::changeYellow(QColor color){
  emit yellowChanged(color);
  updateYellowValues(color);
}

void SlidersColorModel::changeYellowFromSelector(QColor color){
  updateYellowValues(color);
}

void SlidersColorModel::updateYellowValues(QColor color){
  slidersView->ui->ySlider->setY(color);
  
  yellowSpinManualEdit=false;
  slidersView->ui->spYellow->setValue(color.yellow());
  
  slidersView->ui->cSlider->changeYellow(color);
  slidersView->ui->mSlider->changeYellow(color);
  slidersView->ui->kSlider->changeYellow(color);
}

// ===== black =====

void SlidersColorModel::changeBlack(int k){
  if(blackSpinManualEdit){
    QColor filter=QColor::fromCmyk(0, 0, 0, k);
    changeBlack(filter);
  }
  blackSpinManualEdit=true;
}

void SlidersColorModel::changeBlack(QColor color){
  emit blackChanged(color);
  updateBlackValues(color);
}

void SlidersColorModel::changeBlackFromSelector(QColor color){
  updateBlackValues(color);
}

void SlidersColorModel::updateBlackValues(QColor color){
  slidersView->ui->kSlider->setK(color);
  
  blackSpinManualEdit=false;
  slidersView->ui->spBlack->setValue(color.black());
  
  slidersView->ui->cSlider->changeBlack(color);
  slidersView->ui->mSlider->changeBlack(color);
  slidersView->ui->ySlider->changeBlack(color);
}
