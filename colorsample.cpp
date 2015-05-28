#include "colorsample.h"

#include <QPainter>
#include <QDebug>

ColorSample::ColorSample(QWidget *parent) :
  QWidget(parent)
{
  color.setHsv(0, 255, 255);
}

void ColorSample::changeColor(QColor color)
{
  this->color=color;
  repaint();
}

void ColorSample::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.setBrush(color);
  p.drawRect(0, 0, width(), height());
}
