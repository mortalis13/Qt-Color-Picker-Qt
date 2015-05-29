#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>

class HueBar : public QWidget
{
  Q_OBJECT
public:
  explicit HueBar(QWidget *parent = 0);

  QSize sizeHint() const;

signals:
  void hueChanged(QColor);

public slots:

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);

private:
  int max;
  int maxH;
  int barWidth;
  int h,s,v;

  void updateColor(QMouseEvent *e);
  void drawRoundRect(QPainter &p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);
};

#endif // HUEBAR_H
