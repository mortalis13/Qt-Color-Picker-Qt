#ifndef SLIDERSCONTROLLER_H
#define SLIDERSCONTROLLER_H

#include <QtCore>
#include <QColor>

#include <QObject>

#include "Views/sliders.h"

#include "Models/colorprocessor.h"
#include "Models/sliderscolormodel.h"

#include "Widgets/ColorWidgets/hselector.h"
#include "Widgets/ColorWidgets/svselector.h"

#include "Service/vars.h"


class Sliders;
class SlidersColorModel;

// namespace Ui {
// class Sliders;
// }

class SlidersController : public QObject
{
  Q_OBJECT

private:
  Sliders* slidersView;
  SlidersColorModel* slidersColorModel;

public:
  explicit SlidersController(SlidersColorModel* slidersColorModel, QObject* parent=0);
  // explicit SlidersController(Sliders* slidersWindow, QObject* parent=0);
  
  // void setView(Sliders* slidersView);
  

  
private:
  void addActions();
  void init();
  

signals:
  void hueChanged(int);
  void hueChanged(QColor);
  
  void saturationChanged(int);
  void saturationChanged(QColor);
  
  void valueChanged(int);
  void valueChanged(QColor);
  
  
  void redChanged(int);
  void redChanged(QColor);
  
  void greenChanged(int);
  void greenChanged(QColor);
  
  void blueChanged(int);
  void blueChanged(QColor);
  

  void cyanChanged(int);
  void cyanChanged(QColor);
  
  void magentaChanged(int);
  void magentaChanged(QColor);
  
  void yellowChanged(int);
  void yellowChanged(QColor);
  
  void blackChanged(int);
  void blackChanged(QColor);


};

#endif // SLIDERSCONTROLLER_H
