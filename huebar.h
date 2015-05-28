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
  void colorChanged(QColor);

public slots:

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);

private:
  int x, y, r;
  int mx, my;

  int h,s,v;

  QColor color;
  void updateColor(QMouseEvent *e);
};

#endif // HUEBAR_H
