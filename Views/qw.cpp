#include "qw.h"
#include "ui_qw.h"

QW::QW(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QW)
{
  ui->setupUi(this);
}

QW::~QW()
{
  delete ui;
}
