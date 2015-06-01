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


public slots:
  void changeHue(QColor color);
  void changeHueFromSelector(QColor color);
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
  void hueChanged(QColor);

  void ctrlPressed();
  void ctrlReleased();
private slots:
  void setH(int x);
};

#endif // SLIDERS_H
