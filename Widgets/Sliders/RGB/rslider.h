#ifndef RSLIDER_H
#define RSLIDER_H

#include <QWidget>

class RSlider : public QWidget
{
  Q_OBJECT
public:
  explicit RSlider(QWidget *parent = 0);

  void setR(qreal r);
  void setR(QColor color);
  
  void changeGreen(QColor color);
  void changeBlue(QColor color);

  void updateColor();
  
protected:
  void paintEvent(QPaintEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);

  void mouseReleaseEvent(QMouseEvent *e);
  void wheelEvent(QWheelEvent* e);
  
private:

  void drawPointer(QPainter &p);
  void correctPointer();
  void movePointer(int x);
  void incPointer(int val=1);
  void decPointer(int val=1);
  
  void calcVars();
  int normalizePointerX(qreal val);
  qreal normalizeR(int val);

  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


private:
  bool rSliderDrawn;
  bool middlePresed;
  bool ctrlHeld;
  bool widthChanged;

  QPixmap rSliderPixmap;
  QColor color;
  
  qreal r,g,b;
  
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


signals:
  void redChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();
  
};

#endif // RSLIDER_H
