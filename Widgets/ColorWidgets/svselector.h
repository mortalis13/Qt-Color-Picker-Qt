#ifndef SATVALUESELECTOR_H
#define SATVALUESELECTOR_H

#include <QWidget>
#include <QList>
#include <QPixmap>


class SVSelector : public QWidget
{
  Q_OBJECT
  
public:
  explicit SVSelector(QWidget *parent = 0);

  void setS(QColor color);
  void setS(int s);
  
  void setV(QColor color);
  void setV(int v);
  
  void setSV(int s, int v);
  void updateColor();


protected:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);
  void wheelEvent(QWheelEvent *e);


private:
  void drawPointer(QPainter &p);
  void correctPointer();
  void movePointer(int x, int y);

  void incPointerX();
  void decPointerX();
  void decPointerY();
  void incPointerY();

  void drawBorder(QPainter& p);
  void drawCircle(QPainter &p);
  
  void hideCursor(QMouseEvent *e);
  void restoreCursor();

  
private:  
  bool middlePresed;
  bool shiftHeld;
  bool hueLayerDrawn;
  QImage hueLayerImage;
  
  int h,s,v;
  
  int selectorX;
  int selectorY;
  
  int pointerX;
  int pointerY;
  
  
signals:
  void colorChanged(QColor);
  void saturationChanged(QColor);
  void middlePressedSignal(QMouseEvent* e);

public slots:
  void changeHue(QColor color);  

  void shiftPressed();
  void shiftReleased();
};

#endif // SATVALUESELECTOR_H
