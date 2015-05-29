#include "satvalueselector.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

SatValueSelector::SatValueSelector(QWidget *parent) :
  QWidget(parent)
{
  hueLayerDrawn=false;
  
  max=255;
  border=2;
  selectorWidth=max+1;
  
  pointerX=max;
  pointerY=0;
  pointerR=5;
  pointerBorder=2;
  
  borderColor.setRgb(80,80,80,200);
  pointerBorderColor.setNamedColor("#ddd");
  pointerFillColor.setNamedColor("#333");

  h=0;
  s=max;
  v=max;
}

void SatValueSelector::normalizeHsv(){
  h=qMax(0, h);
  h=qMin(maxH, h);

  s=qMax(0, s);
  s=qMin(max, s);

  v=qMax(0, v);
  v=qMin(max, v);
}

void SatValueSelector::correctPointer(){
  qDebug() << QString("[%1, %2]: Before Pointer correction").arg(pointerX).arg(pointerY);
  
  pointerX=s+border;
  pointerY=max-v+border;
  
  qDebug() << QString("[%1, %2]: Pointer corrected").arg(pointerX).arg(pointerY);
  qDebug();
}

void SatValueSelector::changeHue(QColor color)
{
  hueLayerDrawn=false;
  
  h=color.hue();
  normalizeHsv();
  correctPointer();

  QColor newColor;
  newColor.setHsv(h, s, v);

  update();
  emit colorChanged(newColor);
}

void SatValueSelector::paintEvent(QPaintEvent *event)
{
  QColor color;
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  selectorX=border;

  if(!hueLayerDrawn){
    hueLayerImage=QImage(max+1, max+1, QImage::Format_RGB32);
    for(int s=0; s<=max; s++){
      for(int v=0; v<=max; v++){
        color.setHsv(h, s, v);
        hueLayerImage.setPixel(s, max-v, color.rgb());
      }
    }
    
    hueLayerDrawn=true;
  }
  p.drawImage(border, border, hueLayerImage);
  
  drawPointer(p);
  drawBorder(p);
}

void SatValueSelector::drawBorder(QPainter& p){
  QRectF rectangle(selectorX-border, 0, selectorWidth+2*border, height());
  drawRoundRect(p, rectangle, border, 10, borderColor);
}

void SatValueSelector::drawPointer(QPainter& p){
  drawCircle(p);
}

void SatValueSelector::drawCircle(QPainter& p){
  QPen pen(pointerBorderColor, pointerBorder);
  p.setPen(pen);
  p.setBrush(pointerFillColor);
  p.drawEllipse( QPoint(pointerX, pointerY), pointerR, pointerR );
}

void SatValueSelector::drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor)
{
  QPen pen;
  pen.setWidth(borderSize);
  pen.setColor(borderColor);

  p.setPen(pen);
  p.setBrush(Qt::NoBrush);

  QRectF rect(sizeRect.x() + borderSize/2, sizeRect.y() + borderSize/2,
              sizeRect.width() - borderSize, sizeRect.height() - borderSize);

  if(borderSize % 2 == 0)
    p.drawRoundedRect(rect, borderSize, borderSize);
  else
    p.drawRoundedRect(rect.translated(0.5, 0.5), borderRadius, borderRadius);
}

void SatValueSelector::mousePressEvent(QMouseEvent *e)
{
  updateColor(e);
  movePointer(e);
}

void SatValueSelector::mouseMoveEvent(QMouseEvent *e)
{
  updateColor(e);
  movePointer(e);
}

void SatValueSelector::movePointer(QMouseEvent* e){
  pointerX=e->x();
  pointerY=e->y();
  repaint();
}

void SatValueSelector::updateColor(QMouseEvent* e){
  s=e->x() - border;
  v=max - (e->y() - border);

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
