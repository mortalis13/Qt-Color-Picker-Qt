#include "colorwidget.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "Service/services.h"


// ----------------------------------------------------------------------------------------------------

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent) {
  selectorDrawn = false;
  middlePresed = false;
  
  shiftHeld = false;
  ctrlHeld = false;
 
  pointerY = 0;
  
  h = 0;
  s = maxSV;
  v = maxSV;
  
  hf = 0;
  sf = maxF;
  vf = maxF;
  
  color.setHsv(h, s, v);
}


// ---------------------------------------------- service ----------------------------------------------

void ColorWidget::drawCircle(QPainter& p) {
  QPen pen(pointerBorderColor, pointerBorder);
  p.setPen(pen);
  p.setBrush(pointerColor);
  p.drawEllipse( QPoint(pointerX, pointerY), pointerR, pointerR );
}

void ColorWidget::drawRightTrapezoid(QPainter& p) {
  QPen pen(Qt::NoPen);
  pen.setCapStyle(Qt::FlatCap);
  QBrush brush(pointerColor);
  p.setPen(pen);
  p.setBrush(brush);

  QPolygonF triangle;

  QPoint p1( width() - pointerWidth, pointerY + pointerDy1 );
  QPoint p2( width() - pointerWidth, pointerY - pointerDy1 );
  QPoint p3( width(), pointerY - pointerDy2 );
  QPoint p4( width(), pointerY + pointerDy2 );

  triangle << p1 << p2 << p3 << p4;
  
  QPainterPath path;
  path.addPolygon(triangle);
  p.drawPath(path);
}

void ColorWidget::hideCursor(QMouseEvent *e) {
  int x = e->x();
  int y = e->y();

  if ( ( x<minPointerXY || x>maxPointerXY ) || ( y<minPointerXY || y>maxPointerXY ) ) {
    restoreCursor();
    return;
  }
  this->setCursor( QCursor(Qt::BlankCursor) );
}

void ColorWidget::restoreCursor() {
  this->setCursor( QCursor(Qt::ArrowCursor) );
}


// ---------------------------------------------- slots ----------------------------------------------

void ColorWidget::shiftPressed() {
  shiftHeld = true;
}

void ColorWidget::shiftReleased() {
  shiftHeld = false;
}

void ColorWidget::ctrlPressed() {
  ctrlHeld = true;
}

void ColorWidget::ctrlReleased() {
  ctrlHeld = false;
}

// ---------------------------------------------- other ----------------------------------------------

void ColorWidget::log(QString format, int var) {
 qDebug() << QString(format).arg(var);
}

void ColorWidget::log(QString format, qreal var) {
 qDebug() << QString(format).arg(var);
}
