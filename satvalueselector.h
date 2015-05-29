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
  QColor color;
  QList<QImage> hues;

  int max;
  int maxH;
  int h,s,v;

  int mx, my;
  int maxValue;

  void updateColor(QMouseEvent *e);
  void loadHuesFromFile();
  void paintFromList(QPainter *p);
};

#endif // SATVALUESELECTOR_H
