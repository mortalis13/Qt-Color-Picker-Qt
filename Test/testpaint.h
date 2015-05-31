#ifndef TESTPAINT_H
#define TESTPAINT_H

#include <QWidget>

class TestPaint : public QWidget
{
  Q_OBJECT
  void smallLines(QPainter &p);
  void largeLines(QPainter &p);
public:
  explicit TestPaint(QWidget *parent = 0);

signals:

public slots:

protected:
  void paintEvent(QPaintEvent *event);
};

#endif // TESTPAINT_H
