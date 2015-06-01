#ifndef SLIDERS_H
#define SLIDERS_H

#include <QMainWindow>

namespace Ui {
class Sliders;
}

class Sliders : public QMainWindow
{
  Q_OBJECT

public:
  explicit Sliders(QWidget *parent = 0);
  ~Sliders();

private:
  Ui::Sliders *ui;
};

#endif // SLIDERS_H
