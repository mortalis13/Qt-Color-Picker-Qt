#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>

class HueBar : public QWidget
{
  Q_OBJECT
public:
  explicit HueBar(QWidget *parent = 0);

  QSize sizeHint() const;
  void setHue(int hue);

  void setHueFromText(int hue);
signals:
  void hueChangedManually(QColor);
  void hueChangedFromText(QColor);

public slots:
  void changePointerSize(double size);

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);

private:
  bool hueBarDrawn;
  
  QPixmap hueBarPixmap;
  
  int max;
  int maxH;

  int barWidth;
  int barX;
  int barY;
  int pointerWidth;

  int border;
  int h,s,v;

  int pointerY;
  int triangleDy;
  int pointerDy1, pointerDy2;

  QColor pointerColor;
  QColor borderColor;

  void updateColor(QMouseEvent *e);
  void drawRoundRect(QPainter &p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);
  void movePointer(QMouseEvent *e);
  
  void drawPointer(QPainter &p);
  void drawBorder(QPainter& p);
  
  void drawLeftTriangle(QPainter &p);
  void drawRightTriangle(QPainter &p);
  void drawRightTrapezoid(QPainter &p);
  void correctPointer();
};

#endif // HUEBAR_H
