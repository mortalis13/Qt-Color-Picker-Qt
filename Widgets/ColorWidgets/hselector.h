#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>
#include <QMouseEvent>

class HSelector : public QWidget
{
  Q_OBJECT
  
public:
  explicit HSelector(QWidget *parent = 0);

  void setH(int h);
  void setH(QColor color);
  
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
  void incPointer();
  void decPointer();
  
  void drawBorder(QPainter& p);
  void drawRightTrapezoid(QPainter &p);
  

private:
  bool middlePresed;
  bool hSelectorDrawn;
  QPixmap hSelectorPixmap;
  
  int h,s,v;
  int barSize;
  int pointerY;

signals:
  void hueChanged(QColor);
  void middlePressedSignal(QMouseEvent* e);

public slots:

};

#endif // HUEBAR_H
