#ifndef HSLIDER_H
#define HSLIDER_H

#include <QWidget>

class HSlider : public QWidget
{
  Q_OBJECT
public:
  explicit HSlider(QWidget *parent = 0);

  void setH(qreal h);
  void setH(QColor color);
  
  void changeValue(QColor color);
  void changeSaturation(QColor color);
  void updatePaint();
  

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
  qreal normalizeH(int val);

  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


private:
  bool middlePresed;
  bool hSliderDrawn;
  bool ctrlHeld;
  bool widthChanged;

  QColor color;
  QPixmap hSliderPixmap;
  
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
  void hueChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();

};

#endif // HSLIDER_H
