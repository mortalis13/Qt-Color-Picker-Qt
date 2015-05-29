#include "satvalueselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

SatValueSelector::SatValueSelector(QWidget *parent) :
  QWidget(parent)
{
  h=0;
  s=255;
  v=255;
  maxValue=255;
  
  int max=255;
  
//  for(int h=0;h<360;h++){
//    QPixmap pm(max, max);
//    QPainter p(&pm);
    
//    for(int v=255;v>0;v--){
//      for(int s=0;s<255;s++){
//        QColor c;
//        c.setHsv(h, s, v);
//        p.setPen(c);
//        p.drawPoint(s, max-v);
//      }
//    }
    
//    hues.append(pm);
//  }


//  QFile file("hues.dat");
//  if( !file.open(QIODevice::ReadOnly) ){
//    qDebug("Cannot open file");
//    return;
//  }

//  QDataStream stream(&file);
//  stream >> hues;
//  file.close();
  
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
  int size=255;
  int maxCoordinate=size-1;
  QColor color;
  

//  QPainter p(this);
//  p.drawImage(0, 0, hues.at(h));


  QPainter p(this);
  QImage image(size, size, QImage::Format_RGB32);
  for(int s=0; s<255; s++){
    for(int v=0; v<255; v++){
      color.setHsv(h, s, v);
      image.setPixel(s, maxCoordinate-v, color.rgb());
    }
  }
  p.drawImage(0, 0, image);


//  QPixmap pixmap(size, size);
//  QPainter p(&pixmap);
//  for(int s=0; s<255; s++){
//    for(int v=0; v<255; v++){
//      color.setHsv(h, s, v);
//      p.setPen(color);
//      p.drawPoint(s, maxValue-v);
//    }
//  }
//  QPainter wp(this);
//  wp.drawPixmap(0, 0, pixmap);
  

  // QColor color;
  // for(int s=0; s<255; s++){
  //   for(int v=0; v<255; v++){
  //     color.setHsv(h, s, v);
  //     p.setPen(color);
  //     p.drawPoint(s, maxValue-v);
  //   }
  // }

//  QPainter wp(this);
//  wp.drawPixmap(0, 0, hues.at(h));
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
  mx=e->x();
  my=e->y();

  s=mx;
  v=255-my;

  if(s<0 || s>255) return;
  if(v<0 || v>255) return;

  color.setHsv(h, s, v);
  emit colorChanged(color);

//  qDebug() << QString("Coordinates: %1, %2").arg(mx).arg(my);
}
