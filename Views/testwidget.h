#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
  Q_OBJECT

public:
  explicit TestWidget(QWidget *parent = 0);
  ~TestWidget();

private:
  Ui::TestWidget *ui;
  
  int mx, my;
  

protected:
  void paintEvent(QPaintEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  // void mouseReleaseEvent(QMouseEvent *e);

};

#endif // TESTWIDGET_H
