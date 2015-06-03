#ifndef HSVSLIDER_H
#define HSVSLIDER_H

#include "Widgets/Sliders/colorslider.h"

class HSVSlider : public ColorSlider
{
  Q_OBJECT
  
public:
  enum SliderType{Hue, Saturation, Value};
    
private:
  qreal h,s,v;
  SliderType sliderType;
  
  
public:
  HSVSlider(QWidget *parent = 0);

  void setType(SliderType type);
  void init();

  void setH(QColor color);
  void setS(QColor color);
  void setV(QColor color);
  
  void changeHue(QColor color);
  void changeValue(QColor color);
  void changeSaturation(QColor color);
  

protected:
  void paintEvent(QPaintEvent* e);
  void updateColor();
  
private:
  void paintComponent();
  void updateSlider();
  void setColorComponent(QColor color, SliderType stype);
  
  void paintHue(QLinearGradient &grad);
  void paintSaturation(QLinearGradient &grad);
  void paintValue(QLinearGradient &grad);
  
  
signals:
  void hueChanged(QColor);
  void saturationChanged(QColor);
  void valueChanged(QColor);
    
  
};

#endif // HSVSLIDER_H
