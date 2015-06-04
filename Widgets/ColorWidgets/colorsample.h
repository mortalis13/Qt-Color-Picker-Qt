#ifndef COLORSAMPLE_H
#define COLORSAMPLE_H

#include <QWidget>
#include <QMouseEvent>

#include "colorwidget.h"


class ColorSample : public ColorWidget
{
  Q_OBJECT
  
private:
  bool mouseMoving;
  QColor borderColor;
  
public:
  explicit ColorSample(QWidget *parent = 0);
  
  void reupdateColor();
  

signals:
  void colorChanged(QColor color);
  void samplePressedLeft();
  void samplePressedRight();
  void samplePressedMiddle();

public slots:
  void changeColor(QColor color);
  void mouseMovedOnWindow();
  void mouseReleasedOnWindow();

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent* e);
  void enterEvent(QEvent* e);
  void leaveEvent(QEvent *e);

private:
  void drawBorder(QPainter& p);

};

#endif // COLORSAMPLE_H
