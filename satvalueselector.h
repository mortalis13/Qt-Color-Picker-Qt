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
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);

private:  
  int mx, my;
  int h,s,v;
  int maxValue;

  QColor color;
  void updateColor(QMouseEvent *e);
  
  QList<QPixmap> hues;
};

#endif // SATVALUESELECTOR_H
