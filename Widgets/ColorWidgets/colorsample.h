#ifndef COLORSAMPLE_H
#define COLORSAMPLE_H

#include <QWidget>
#include <QMouseEvent>

#include "colorwidget.h"


class ColorSample : public ColorWidget
{
  Q_OBJECT
public:
  explicit ColorSample(QWidget *parent = 0);
  
  void reupdateColor();
  

signals:
  void colorChanged(QColor color);
  void samplePressedLeft();
  void samplePressedRight();

public slots:
  void changeColor(QColor color);
  void mouseMovedOnWindow();

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent* e);
  void enterEvent(QEvent* e);
  void leaveEvent(QEvent *e);

private:
  void drawBorder(QPainter& p);

private:
  bool mouseMoving;
  QColor borderColor;
  
};

#endif // COLORSAMPLE_H
