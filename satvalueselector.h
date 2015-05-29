#ifndef SATVALUESELECTOR_H
#define SATVALUESELECTOR_H

#include <QWidget>
#include <QList>
#include <QPixmap>

class SatValueSelector : public QWidget
{
  Q_OBJECT
public:
  explicit SatValueSelector(QWidget *parent = 0);

signals:
  void colorChanged(QColor);

public slots:
  void changeHue(QColor color);

protected:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

private:  
  QColor color;
  QList<QImage> hues;
  QImage hueLayerImage;
  
  QColor borderColor;
  QColor pointerBorderColor;
  QColor pointerFillColor;
  
  bool hueLayerDrawn;
  
  int selectorX;
  int selectorWidth;
  
  int pointerWidth;
  int pointerBorder;
  
  int pointerX;
  int pointerY;
  int pointerR;

  int border;

  int max;
  int maxH;
  int h,s,v;

  int mx, my;
  int maxValue;

  void drawRoundRect(QPainter &p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);
  
  void movePointer(QMouseEvent *e);

  void updateColor(QMouseEvent *e);
  void loadHuesFromFile();
  void paintFromList(QPainter *p);
  
  void drawPointer(QPainter &p);
  void drawBorder(QPainter& p);
  void drawCircle(QPainter &p);
  
  void normalizeHsv();
  void correctPointer();
  
  void hideCursor();
  void restoreCursor();
};

#endif // SATVALUESELECTOR_H
