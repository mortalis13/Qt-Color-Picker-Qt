#ifndef VSLIDER_H
#define VSLIDER_H

#include <QWidget>

class VSlider : public QWidget
{
  Q_OBJECT
public:
  explicit VSlider(QWidget *parent = 0);

  void setV(qreal v);
  void setV(QColor color);
  
  void changeHue(QColor color);
  void changeSaturation(QColor color);

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
  qreal normalizeV(int val);

  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


private:
  bool middlePresed;
  bool vSliderDrawn;
  bool ctrlHeld;
  bool widthChanged;

  QColor color;
  QPixmap vSliderPixmap;
  
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
  void valueChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();
  
};

#endif // VSLIDER_H
