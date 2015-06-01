#ifndef QW_H
#define QW_H

#include <QMainWindow>

namespace Ui {
class QW;
}

class QW : public QMainWindow
{
  Q_OBJECT

public:
  explicit QW(QWidget *parent = 0);
  ~QW();

private:
  Ui::QW *ui;
};

#endif // QW_H
