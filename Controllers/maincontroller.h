#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QColor>
#include <QObject>

#include "Views/mainwindow.h"
#include "Controllers/sliderscontroller.h"
#include "Models/colorprocessor.h"

#include "Widgets/ColorWidgets/hselector.h"
#include "Widgets/ColorWidgets/svselector.h"


class MainWindow;

class MainController : public QObject
{
  Q_OBJECT

private:
  HSelector* hSelector;
  SVSelector* svSelector;

  ColorProcessor* colorProcessor;
  SlidersController *slidersController;
  
  MainWindow* view;
    
  
public:
  explicit MainController(HSelector* hSelector, SVSelector* svSelector,
                      ColorProcessor *colorProcessor, 
                      MainWindow *view, 
                      QObject* parent=0);
  
  void addSlidersController(SlidersController *slidersController);
  
  
private:
  void changeRGB(int pos, int val);
  void changeCMYK(int pos, int val);
  
  void connectRGB();
  void disconnectRGB();
  void connectCMYK();
  void disconnectCMYK();
  
signals:
  void hueChanged(QColor);
  void saturationChanged(QColor);
  void valueChanged(QColor);
  
  void redChanged(QColor);
  void greenChanged(QColor);
  void blueChanged(QColor);

  void cyanChanged(QColor);
  void magentaChanged(QColor);
  void yellowChanged(QColor);
  void blackChanged(QColor);  
 

public slots:
  void changeHue(QColor color);
  void changeSaturation(QColor color);
  void changeValue(QColor color);
  
  void changeRed(QColor color);
  void changeGreen(QColor color);
  void changeBlue(QColor color);
  
  void changeCyan(QColor color);
  void changeMagenta(QColor color);
  void changeYellow(QColor color);
  void changeBlack(QColor color); 
  
  
};

#endif // MAINCONTROLLER_H
