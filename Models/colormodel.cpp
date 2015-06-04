#include "colormodel.h"

#include "Service/validator.h"


// ------------------------------------------------------------------------------------------------

ColorModel::ColorModel(HSelector *hSelector, SVSelector *svSelector,
                       ColorProcessor *colorProcessor, SlidersController *slidersController, 
                       MainWindow *view,
                       QObject* parent) : QObject(parent)
{
  this->hSelector=hSelector;
  this->svSelector=svSelector;
  this->view=view;
  this->colorProcessor=colorProcessor;
  this->slidersController=slidersController;
  
  addActions();
}

void ColorModel::addActions(){
  connectHSV();
  connectRGB();
  connectCMYK();
}

void ColorModel::connectHSV(){
  connect( this, SIGNAL(hueChanged(QColor)), slidersController, SLOT(changeHueFromSelector(QColor)) );
  connect( this, SIGNAL(saturationChanged(QColor)), slidersController, SLOT(changeSaturationFromSelector(QColor)) );
  connect( this, SIGNAL(valueChanged(QColor)), slidersController, SLOT(changeValueFromSelector(QColor)) );
}

void ColorModel::connectRGB(){
  connect( this, SIGNAL(RGBChanged(QColor)), slidersController, SLOT(changeRedFromSelector(QColor)) );
  connect( this, SIGNAL(RGBChanged(QColor)), slidersController, SLOT(changeGreenFromSelector(QColor)) );
  connect( this, SIGNAL(RGBChanged(QColor)), slidersController, SLOT(changeBlueFromSelector(QColor)) );
}

void ColorModel::disconnectRGB(){
  disconnect( this, SIGNAL(RGBChanged(QColor)), 0, 0 );
}

void ColorModel::connectCMYK(){
  connect( this, SIGNAL(CMYKChanged(QColor)), slidersController, SLOT(changeCyanFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), slidersController, SLOT(changeMagentaFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), slidersController, SLOT(changeYellowFromSelector(QColor)) );
  connect( this, SIGNAL(CMYKChanged(QColor)), slidersController, SLOT(changeBlackFromSelector(QColor)) );
}

void ColorModel::disconnectCMYK(){
  disconnect( this, SIGNAL(CMYKChanged(QColor)), 0, 0 );
}

// --------------------------------------------- HSV ---------------------------------------------

// ===== hue =====
void ColorModel::changeHue(QColor color){
  hSelector->setH(color);
}

// ===== saturation =====
void ColorModel::changeSaturation(QColor color){
  svSelector->setS(color);
}

// ===== value =====
void ColorModel::changeValue(QColor color){
  svSelector->setV(color);
}


// --------------------------------------------- RGB ---------------------------------------------

void ColorModel::changeRGB(int pos, int val){
  QString RGB_Text=view->getRGB();
  QColor currentColor=colorProcessor->getColorRGB(RGB_Text);
  
  switch(pos){
    case 0:
      currentColor.setRed(val);
      break;  
    case 1:
      currentColor.setGreen(val);
      break;  
    case 2:
      currentColor.setBlue(val);
      break;  
  }
  
  disconnectRGB();
  QString RGB=colorProcessor->getRGB(currentColor);
  view->setRGB(RGB);
  view->updateColorRGB(RGB);
  connectRGB();
}

// ===== red =====
void ColorModel::changeRed(QColor color){
  changeRGB(0, color.red());
}

// ===== green =====
void ColorModel::changeGreen(QColor color){
  changeRGB(1, color.green());
}

// ===== blue =====
void ColorModel::changeBlue(QColor color){
  changeRGB(2, color.blue());
}


// --------------------------------------------- CMYK ---------------------------------------------

void ColorModel::changeCMYK(int pos, int val){
  QString CMYK_Text=view->getCMYK();
  QColor currentColor=colorProcessor->getColorCMYK(CMYK_Text);
  
  int c=currentColor.cyan();
  int m=currentColor.magenta();
  int y=currentColor.yellow();
  int k=currentColor.black();
  
  switch(pos){
    case 0:
      c=val;
      break;  
    case 1:
      m=val;
      break;  
    case 2:
      y=val;
      break;  
    case 3:
      k=val;
      break;  
  }
  currentColor.setCmyk(c, m, y, k);
  
  disconnectCMYK();
  QString CMYK=colorProcessor->getCMYK(currentColor);
  view->setCMYK(CMYK);
  view->updateColorCMYK(CMYK);
  connectCMYK();
}

// ===== cyan =====
void ColorModel::changeCyan(QColor color){
  changeCMYK(0, color.cyan());
}

// ===== magenta =====
void ColorModel::changeMagenta(QColor color){
  changeCMYK(1, color.magenta());
}

// ===== yellow =====
void ColorModel::changeYellow(QColor color){
  changeCMYK(2, color.yellow());
}

// ===== black =====
void ColorModel::changeBlack(QColor color){
  changeCMYK(3, color.black());
}
