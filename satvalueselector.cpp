#include "satvalueselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

SatValueSelector::SatValueSelector(QWidget *parent) :
  QWidget(parent)
{
  max=255;

  h=0;
  s=max;
  v=max;
}

void SatValueSelector::changeHue(QColor color)
{
  h=color.hue();
  QColor newColor;
  newColor.setHsv(h, s, v);

  update();
  emit colorChanged(newColor);
}

void SatValueSelector::paintEvent(QPaintEvent *event)
{
  QColor color;

  QPainter p(this);
  QImage image(max+1, max+1, QImage::Format_RGB32);
  for(int s=0; s<=max; s++){
    for(int v=0; v<=max; v++){
      color.setHsv(h, s, v);
      image.setPixel(s, max-v, color.rgb());
    }
  }
  p.drawImage(0, 0, image);
}

void SatValueSelector::mousePressEvent(QMouseEvent *e)
{
  updateColor(e);
}

void SatValueSelector::mouseMoveEvent(QMouseEvent *e)
{
  updateColor(e);
}

void SatValueSelector::updateColor(QMouseEvent* e){
  s=e->x();
  v=max-e->y();

  if(s<0 || s>max) return;
  if(v<0 || v>max) return;

  color.setHsv(h, s, v);
  emit colorChanged(color);

//  qDebug() << QString("Coordinates: %1, %2").arg(e->x()).arg(e->y());
}

void SatValueSelector::loadHuesFromFile()
{
  QFile file("hues.dat");
  if( !file.open(QIODevice::ReadOnly) ){
    qDebug("Cannot open file");
    return;
  }

  QDataStream stream(&file);
  stream >> hues;
  file.close();
}

void SatValueSelector::paintFromList(QPainter* p)
{
  p->drawImage(0, 0, hues.at(h));
}
