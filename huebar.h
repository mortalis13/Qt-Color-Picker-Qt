#ifndef HUEBAR_H
#define HUEBAR_H

#include <QWidget>

class HueBar : public QWidget
{
  Q_OBJECT
public:
  explicit HueBar(QWidget *parent = 0);

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
  int h,s,v;

  void updateColor(QMouseEvent *e);
};

#endif // HUEBAR_H
