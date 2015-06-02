#ifndef SSLIDER_H
#define SSLIDER_H

#include <QWidget>

class SSlider : public QWidget
{
  Q_OBJECT
public:
  explicit SSlider(QWidget *parent = 0);

  void setS(qreal s);
  void setS(QColor color);
  
  void changeHue(QColor color);

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
  
  void calcVars();
  int normalizePointerX(qreal val);
  qreal normalizeS(int val);

  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


private:
  bool middlePresed;
  bool hSliderDrawn;
  bool ctrlHeld;
  bool widthChanged;

  QColor color;
  QPixmap sSliderPixmap;
  
  qreal h,s,v;
  
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
  void saturationChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();
  
};

#endif // SSLIDER_H
