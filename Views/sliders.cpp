#include "sliders.h"
#include "ui_sliders.h"

Sliders::Sliders(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Sliders)
{
  ui->setupUi(this);
}

Sliders::~Sliders()
{
  delete ui;
}
