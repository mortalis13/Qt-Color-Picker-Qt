#ifndef CMYKSLIDER_H
#define CMYKSLIDER_H

#include "Widgets/Sliders/colorslider.h"

class CMYKSlider : public ColorSlider
{
  Q_OBJECT
  
public:
  enum SliderType{Cyan, Magenta, Yellow, Black};
    
private:
  qreal c,m,y,k;
  SliderType sliderType;
  
  
public:
  CMYKSlider(QWidget *parent = 0);

  void setType(SliderType type);
  void init();

  void setC(QColor color);
  void setM(QColor color);
  void setY(QColor color);
  void setK(QColor color);
  
  void changeCyan(QColor color);
  void changeMagenta(QColor color);
  void changeYellow(QColor color);
  void changeBlack(QColor color);
  

protected:
  void paintEvent(QPaintEvent* e);
  void updateColor();
  
private:
  void paintComponent();
  void updateSlider();
  void setColorComponent(QColor color, SliderType stype);
  
  void paintCyan(QLinearGradient &grad);
  void paintMagenta(QLinearGradient &grad);
  void paintYellow(QLinearGradient &grad);
  void paintBlack(QLinearGradient &grad);
  
  
signals:
  void cyanChanged(QColor);
  void magentaChanged(QColor);
  void yellowChanged(QColor);
  void blackChanged(QColor);
  
};

#endif // CMYKSLIDER_H
