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
  void drawBorder(QPainter& p);


private:
  QColor color;
  
};

#endif // COLORSAMPLE_H
