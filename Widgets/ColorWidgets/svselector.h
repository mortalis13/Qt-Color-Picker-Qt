#ifndef SATVALUESELECTOR_H
#define SATVALUESELECTOR_H

#include <QWidget>
#include <QList>
#include <QPixmap>

#include "colorwidget.h"


class SVSelector : public ColorWidget
{
  Q_OBJECT
  
private:
  // QColor color;
  // int h,s,v;
  
  
public:
  explicit SVSelector(QWidget *parent = 0);

  void setS(QColor color);
  void setV(QColor color);
  void setSV(int s, int v);
  
  void reupdateColor();


protected:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);
  void wheelEvent(QWheelEvent *e);


private:
  void updateColor();
  
  void drawPointer(QPainter &p);
  void correctPointer();
  void movePointer(int x, int y);

  void incPointerX(int val);
  void decPointerX(int val);
  void decPointerY(int val);
  void incPointerY(int val);

  void drawBorder(QPainter& p);

  
signals:
  void colorChanged(QColor);
  void saturationChanged(QColor);
  void valueChanged(QColor);

public slots:
  void changeHue(QColor color);  


};

#endif // SATVALUESELECTOR_H
