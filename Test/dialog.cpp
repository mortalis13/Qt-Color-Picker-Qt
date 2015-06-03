#include "dialog.h"
#include "ui_dialog.h"

#include <QStyleFactory>
#include "norwegianwoodstyle.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);

//  QApplication::setStyle(QStyleFactory::create("fusion"));
//    ui->horizontalSlider->setStyle(new NorwegianWoodStyle);
}

Dialog::~Dialog()
{
  delete ui;
}
