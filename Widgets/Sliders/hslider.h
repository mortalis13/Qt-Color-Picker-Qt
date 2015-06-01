#ifndef HSLIDER_H
#define HSLIDER_H

#include <QWidget>

class HSlider : public QWidget
{
  Q_OBJECT
public:
  explicit HSlider(QWidget *parent = 0);

  void setH(int h);

protected:
  void paintEvent(QPaintEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);

  void mouseReleaseEvent(QMouseEvent *e);
  void wheelEvent(QWheelEvent* e);
  
private:
  void updateColor();

  void drawPointer(QPainter &p);
  void correctPointer();
  void movePointer(int x);
  void incPointer();
  void decPointer();

  void drawBorder(QPainter& p);
  void drawRightTrapezoid(QPainter &p);

  void hideCursor(QMouseEvent *e);
  void restoreCursor();


private:
  bool middlePresed;
  bool hSliderDrawn;
  QPixmap hSliderPixmap;
  
  int h,s,v;
  
  int pointerX;
  int pointerY;
  
  int minPointerX;
  int maxPointerX;
  
  int sliderX;
  int sliderY;
  int sliderW;
  int sliderH;

signals:
  void hueChanged(QColor);
  void middlePressedSignal(QMouseEvent* e);

public slots:  

};

#endif // HSLIDER_H
