#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QWidget>

class ColorSlider : public QWidget
{
  Q_OBJECT
public:
  explicit ColorSlider(QWidget *parent = 0);

  void updatePaint();

protected:
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);

  void mouseReleaseEvent(QMouseEvent *e);
  void wheelEvent(QWheelEvent* e);
  
protected:
  virtual void updateColor();

  qreal normalizeVal(int val);
  int normalizePointerX(qreal val);

  void drawPointer(QPainter &p);
  void correctPointer();
  void movePointer(int x);
  void incPointer(int val=1);
  void decPointer(int val=1);
  
  void calcVars(qreal val);
  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


protected:
  const qreal maxF=1.0;
  
  bool sliderDrawn;
  QPixmap sliderPixmap;
  
  bool middlePresed;
  bool ctrlHeld;
  bool widthChanged;

  QColor color;
  
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
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();

};

#endif // COLORSLIDER_H
