#include "sliderscontroller.h"

// #include "Service/validator.h"
// #include "ui_sliders.h"


// ------------------------------------------------------------------------------------------------

SlidersController::SlidersController(SlidersColorModel* slidersColorModel, QObject* parent) : QObject(parent)
{
  this->slidersColorModel=slidersColorModel;
  
  addActions();
}

void SlidersController::init(){
}

// void SlidersController::setView(Sliders* slidersView){
//   this->slidersView=slidersView;
// }

void SlidersController::addActions(){
  connect( this, SIGNAL(hueChanged(QColor)), slidersColorModel, SLOT(changeHue(QColor)) );
  connect( this, SIGNAL(saturationChanged(QColor)), slidersColorModel, SLOT(changeSaturation(QColor)) );
  connect( this, SIGNAL(valueChanged(QColor)), slidersColorModel, SLOT(changeValue(QColor)) );
  
  connect( this, SIGNAL(redChanged(QColor)), slidersColorModel, SLOT(changeRed(QColor)) );
  connect( this, SIGNAL(greenChanged(QColor)), slidersColorModel, SLOT(changeGreen(QColor)) );
  connect( this, SIGNAL(blueChanged(QColor)), slidersColorModel, SLOT(changeBlue(QColor)) );

  connect( this, SIGNAL(cyanChanged(QColor)), slidersColorModel, SLOT(changeCyan(QColor)) );
  connect( this, SIGNAL(magentaChanged(QColor)), slidersColorModel, SLOT(changeMagenta(QColor)) );
  connect( this, SIGNAL(yellowChanged(QColor)), slidersColorModel, SLOT(changeYellow(QColor)) );
  connect( this, SIGNAL(blackChanged(QColor)), slidersColorModel, SLOT(changeBlack(QColor)) );


  connect( this, SIGNAL(hueChanged(int)), slidersColorModel, SLOT(changeHue(int)) );
  connect( this, SIGNAL(saturationChanged(int)), slidersColorModel, SLOT(changeSaturation(int)) );
  connect( this, SIGNAL(valueChanged(int)), slidersColorModel, SLOT(changeValue(int)) );
  
  connect( this, SIGNAL(redChanged(int)), slidersColorModel, SLOT(changeRed(int)) );
  connect( this, SIGNAL(greenChanged(int)), slidersColorModel, SLOT(changeGreen(int)) );
  connect( this, SIGNAL(blueChanged(int)), slidersColorModel, SLOT(changeBlue(int)) );
  
  connect( this, SIGNAL(cyanChanged(int)), slidersColorModel, SLOT(changeCyan(int)) );
  connect( this, SIGNAL(magentaChanged(int)), slidersColorModel, SLOT(changeMagenta(int)) );
  connect( this, SIGNAL(yellowChanged(int)), slidersColorModel, SLOT(changeYellow(int)) );
  connect( this, SIGNAL(blackChanged(int)), slidersColorModel, SLOT(changeBlack(int)) );
}
