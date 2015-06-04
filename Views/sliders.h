#ifndef SLIDERS_H
#define SLIDERS_H

#include <QMainWindow>
#include <QMouseEvent>

#include "Controllers/sliderscontroller.h"


namespace Ui {
class Sliders;
}

class SlidersController;

class Sliders : public QMainWindow
{
  Q_OBJECT

public:
  Ui::Sliders *ui;
  
private:
  bool mouseDown;
  bool mouseMoved;
  int mx, my;  
  
  SlidersController *slidersController;  
  
public:
  explicit Sliders(SlidersController *slidersController, QWidget *parent = 0);
  ~Sliders();

  
protected:
  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  

private:
  void addActions();
  void addKeyActions();
  void addShortcuts();
  void init();
  
  
signals:

  void ctrlPressed();
  void ctrlReleased();
  
  
private slots:
  void sliderMiddlePressed(QMouseEvent* e);
  
  
};

#endif // SLIDERS_H
