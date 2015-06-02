#ifndef SLIDERS_H
#define SLIDERS_H

#include <QMainWindow>
#include <QMouseEvent>


namespace Ui {
class Sliders;
}

class Sliders : public QMainWindow
{
  Q_OBJECT

public:
  explicit Sliders(QWidget *parent = 0);
  ~Sliders();


protected:
  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  

private:
  Ui::Sliders *ui;

  bool mouseDown;
  bool mouseMoved;
  int mx, my;  
  
  void addActions();
  void init();
  
  
  
signals:
  void hueChanged(int);
  void hueChanged(QColor);
  
  void saturationChanged(int);
  void saturationChanged(QColor);
  
  void valueChanged(int);
  void valueChanged(QColor);

  void ctrlPressed();
  void ctrlReleased();
  
public slots:
  void changeHue(int h);
  void changeHue(QColor color);
  void changeHueFromSelector(QColor color);
  
  void changeSaturation(int s);
  void changeSaturation(QColor color);
  void changeSaturationFromSelector(QColor color);  
  
  void changeValue(int s);
  void changeValue(QColor color);
  void changeValueFromSelector(QColor color);  
  
};

#endif // SLIDERS_H
