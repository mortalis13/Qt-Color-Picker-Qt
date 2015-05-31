#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>

class HSelector : public QWidget
{
  Q_OBJECT
  
public:
  explicit HSelector(QWidget *parent = 0);

  void setH(int h);
  
signals:
  void hueChanged(QColor);

public slots:

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void mouseReleaseEvent(QMouseEvent *e);

private:
  void updateColor();
  
  void drawPointer(QPainter &p);
  void movePointer(QMouseEvent *e);
  void correctPointer();
  
  void drawBorder(QPainter& p);
  void drawRightTrapezoid(QPainter &p);
  
private:
  bool hSelectorDrawn;
  QPixmap hSelectorPixmap;
  
  int h,s,v;
  int pointerY;

};

#endif // HUEBAR_H
