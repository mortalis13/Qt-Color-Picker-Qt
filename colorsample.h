#ifndef COLORSAMPLE_H
#define COLORSAMPLE_H

#include <QWidget>

class ColorSample : public QWidget
{
  Q_OBJECT
public:
  explicit ColorSample(QWidget *parent = 0);

signals:

public slots:
  void changeColor(QColor color);

protected:
  void paintEvent(QPaintEvent *event);

private:
  QColor color;
  QColor borderColor;
  
  int border;
  
  void drawBorder(QPainter& p);
  void drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);
  
};

#endif // COLORSAMPLE_H
