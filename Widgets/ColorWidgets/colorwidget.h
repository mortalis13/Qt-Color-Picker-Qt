#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>


class ColorWidget : public QWidget
{
  Q_OBJECT
  
  
protected:
  const int maxH=360;
  const int maxSV=255;
  const qreal maxF=1.0;
  
  const qreal ratio=1.0/maxH;
  

  const int border=2;
  const int borderRadius=10;

  const int selectorX=border;
  const int selectorY=border;

  const QColor borderColor=QColor(80,80,80,200);
  const QColor pointerColor=QColor("#333");
  
  
// --- H ---
  const int barWidth=40;

  const int minPointerY = border;
  const int maxPointerY = maxH + minPointerY;

  const int pointerWidth=10;
  const int pointerDy1=1.5;
  const int pointerDy2=5;
  
  
// --- SV ---
  const int selectorSize=maxSV+1;
  const int minPointerXY = border;
  const int maxPointerXY = maxSV+border;

  const int pointerR=5;
  const int pointerBorder=2;

  const QColor pointerBorderColor=QColor("#ddd");  
  
  
protected:  
  bool middlePresed;
  bool selectorDrawn;
  bool shiftHeld;
  bool ctrlHeld;
  
  QPixmap hSelectorPixmap;
  QImage hueLayerImage;
  QColor color;
  
  int h,s,v;
  qreal hf,sf,vf;
  
  int pointerX;
  int pointerY;
    
  
public:
  explicit ColorWidget(QWidget *parent = 0);


protected:
  void drawCircle(QPainter &p);
  void drawRightTrapezoid(QPainter& p);
  
  void hideCursor(QMouseEvent *e);
  void restoreCursor();

  void log(QString format, int var);
  void log(QString format, qreal var);
  
  
signals:
  void middlePressedSignal(QMouseEvent* e);
  

public slots:
  void shiftPressed();
  void shiftReleased();
  void ctrlPressed();
  void ctrlReleased();
  
  
};

#endif // COLORWIDGET_H
