#include "maincontroller.h"


MainController::MainController(HSelector *hSelector, SVSelector *svSelector,
                       ColorProcessor *colorProcessor, 
                       MainWindow *view,
                       QObject* parent) : QObject(parent)
{
  this->hSelector=hSelector;
  this->svSelector=svSelector;
  this->view=view;
  this->colorProcessor=colorProcessor;
  
  slidersController=NULL;
}

void MainController::addSlidersController(SlidersController *slidersController){
  this->slidersController=slidersController;
}

void MainController::connectRGB(){
  if(slidersController!=NULL)
    slidersController->connectRGB();
}

void MainController::disconnectRGB(){
  if(slidersController!=NULL)
    slidersController->disconnectRGB();
}

void MainController::connectCMYK(){
  if(slidersController!=NULL)
    slidersController->connectCMYK();
}

void MainController::disconnectCMYK(){
  if(slidersController!=NULL)
    slidersController->disconnectCMYK();
}


// --------------------------------------------- HSV ---------------------------------------------

// ===== hue =====
void MainController::changeHue(QColor color){
  hSelector->setH(color);
}

// ===== saturation =====
void MainController::changeSaturation(QColor color){
  svSelector->setS(color);
}

// ===== value =====
void MainController::changeValue(QColor color){
  svSelector->setV(color);
}


// --------------------------------------------- RGB ---------------------------------------------

void MainController::changeRGB(int pos, int val){
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
void MainController::changeRed(QColor color){
  changeRGB(0, color.red());
}

// ===== green =====
void MainController::changeGreen(QColor color){
  changeRGB(1, color.green());
}

// ===== blue =====
void MainController::changeBlue(QColor color){
  changeRGB(2, color.blue());
}


// --------------------------------------------- CMYK ---------------------------------------------

void MainController::changeCMYK(int pos, int val){
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
void MainController::changeCyan(QColor color){
  changeCMYK(0, color.cyan());
}

// ===== magenta =====
void MainController::changeMagenta(QColor color){
  changeCMYK(1, color.magenta());
}

// ===== yellow =====
void MainController::changeYellow(QColor color){
  changeCMYK(2, color.yellow());
}

// ===== black =====
void MainController::changeBlack(QColor color){
  changeCMYK(3, color.black());
}
