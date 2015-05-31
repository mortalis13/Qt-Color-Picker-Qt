#ifndef COLORSAMPLE_H
#define COLORSAMPLE_H

#include <QWidget>
#include <QMouseEvent>


class ColorSample : public QWidget
{
  Q_OBJECT
public:
  explicit ColorSample(QWidget *parent = 0);

signals:
  void samplePressedLeft();
  void samplePressedRight();

public slots:
  void changeColor(QColor color);
  void mouseMovedOnWindow();

protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent* e);
  void enterEvent(QEvent* e);
  void leaveEvent(QEvent *e);

private:
  void drawBorder(QPainter& p);

private:
  bool mouseMoving;

  QColor color;
  QColor borderColor;
  
};

#endif // COLORSAMPLE_H
