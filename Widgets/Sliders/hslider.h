#ifndef HSLIDER_H
#define HSLIDER_H

#include <QWidget>

class HSlider : public QWidget
{
  Q_OBJECT
public:
  explicit HSlider(QWidget *parent = 0);

//  void setH(double h);
  void setH(int h, double hf);

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
  void incPointer(int val=1);
  void decPointer(int val=1);

  void drawBorder(QPainter& p);
  void drawRightTrapezoid(QPainter &p);

  void hideCursor(QMouseEvent *e);
  void restoreCursor();

  void log(QString format, QVariant var);


private:
  bool middlePresed;
  bool hSliderDrawn;
  bool ctrlHeld;
  bool widthChanged;

  QPixmap hSliderPixmap;
  
//  int h,s,v;

  double h,s,v;
  
  int pointerX;
  int pointerY;
  
  int minPointerX;
  int maxPointerX;
  
  int sliderX;
  int sliderY;
  int sliderW;
  int sliderH;
  int prevSliderW;

  int sliderVal;
  int maxRange;

  double normalizeH(int val);

  void calcVars();
  int normalizePointerX(double val);

signals:
  void hueChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  

void ctrlPressed();
void ctrlReleased();

};

#endif // HSLIDER_H
