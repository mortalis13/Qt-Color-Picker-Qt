#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>

class HueBar : public QWidget
{
  Q_OBJECT
  
public:
  explicit HueBar(QWidget *parent = 0);

  void setH(int h);
  
signals:
  void hueChanged(QColor);

public slots:

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);

private:
  void updateColor();
  
  void drawPointer(QPainter &p);
  void movePointer(QMouseEvent *e);
  void correctPointer();
  
  void drawBorder(QPainter& p);
  void drawRightTrapezoid(QPainter &p);
  
private:
  bool hueBarDrawn;
  QPixmap hueBarPixmap;
  
  int h,s,v;
  int pointerY;

};

#endif // HUEBAR_H
