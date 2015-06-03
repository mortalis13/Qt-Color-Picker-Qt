#ifndef RGBSLIDER_H
#define RGBSLIDER_H

#include "Widgets/Sliders/colorslider.h"

class RGBSlider : public ColorSlider
{
  Q_OBJECT
  
public:
  enum SliderType{Red, Green, Blue};
    
private:
  qreal r,g,b;
  SliderType sliderType;
  
  
public:
  RGBSlider(QWidget *parent = 0);

  void setType(SliderType type);
  void init();

  void setR(QColor color);
  void setG(QColor color);
  void setB(QColor color);
  
  void changeRed(QColor color);
  void changeGreen(QColor color);
  void changeBlue(QColor color);
  

protected:
  void paintEvent(QPaintEvent* e);
  void updateColor();
  
private:
  void paintComponent();
  void updateSlider();
  void setColorComponent(QColor color, SliderType stype);
  
  void paintRed(QLinearGradient &grad);
  void paintGreen(QLinearGradient &grad);
  void paintBlue(QLinearGradient &grad);
  
  
signals:
  void redChanged(QColor);
  void greenChanged(QColor);
  void blueChanged(QColor);
  
};

#endif // RGBSLIDER_H
