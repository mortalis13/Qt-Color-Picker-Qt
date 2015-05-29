#include "testpaint.h"

#include <QPainter>
#include <QDebug>

TestPaint::TestPaint(QWidget *parent) :
  QWidget(parent)
{
}

void TestPaint::smallLines(QPainter& p){
  p.setPen(Qt::black);
  int lines=0;

  for(int i=0; i<=height(); i+=4){
    p.drawLine(0, i, width(), i);
    lines++;
  }

  qDebug() << "smallLines: " << lines;
}

void TestPaint::largeLines(QPainter& p){
  QPen pen(QColor(0,0,0), 2);
  p.setPen(pen);
  int hlines=0, vlines=0;

  for(int i=0; i<=height(); i+=40){
    p.drawLine(0, i, width(), i);
    hlines++;
  }

  for(int i=0; i<=width(); i+=40){
    p.drawLine(i, 0, i, height());
    vlines++;
  }

  qDebug() << QString("largeLines: %1 h, %2 v").arg(hlines).arg(vlines);
}

void TestPaint::paintEvent(QPaintEvent *event)
{
  QPainter p(this);

//  smallLines(p);
  largeLines(p);
}

