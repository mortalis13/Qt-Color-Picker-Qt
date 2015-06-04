#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>
#include <QMouseEvent>

#include "colorwidget.h"


class HSelector : public ColorWidget
{
  Q_OBJECT
  
private:
  int barSize;
  // QColor color;
  // int h,s,v;
  
  
public:
  explicit HSelector(QWidget *parent = 0);

  void setH(int h);
  void setH(QColor color);
  void setInitH(int h);
  
  void reupdateColor();
  
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
  void movePointer(int y);
  void incPointer(int val);
  void decPointer(int val);
  
  void drawBorder(QPainter& p);
  

signals:
  void hueChanged(QColor);


};

#endif // HUEBAR_H
