#ifndef SLIDERS_H
#define SLIDERS_H

#include <QDialog>

namespace Ui {
class Sliders;
}

class Sliders : public QDialog
{
  Q_OBJECT

public:
  explicit Sliders(QWidget *parent = 0);
  ~Sliders();

private:
  Ui::Sliders *ui;
  void init();
};

#endif // SLIDERS_H
