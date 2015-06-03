#ifndef GSLIDER_H
#define GSLIDER_H

#include <QWidget>

class GSlider : public QWidget
{
  Q_OBJECT
public:
  explicit GSlider(QWidget *parent = 0);

  void setG(qreal g);
  void setG(QColor color);
  
  void changeRed(QColor color);
  void changeBlue(QColor color);

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
  qreal normalizeG(int val);

  void drawBorder(QPainter& p);

  void log(QString format, int var);
  void log(QString format, qreal var);


private:
  bool gSliderDrawn;
  bool middlePresed;
  bool ctrlHeld;
  bool widthChanged;

  QPixmap gSliderPixmap;
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
  void greenChanged(QColor);
  void pointerMoved(int);
  void middlePressedSignal(QMouseEvent* e);

public slots:  
  void ctrlPressed();
  void ctrlReleased();
  
};

#endif // GSLIDER_H
