#include "sliders.h"
#include "ui_sliders.h"

#include "Service/sliderstyle.h"

#include <QStyleFactory>
#include "norwegianwoodstyle.h"

Sliders::Sliders(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Sliders)
{
  ui->setupUi(this);

  init();
}

Sliders::~Sliders()
{
  delete ui;
}

void Sliders::init()
{
  // setAttribute(Qt::WA_DeleteOnClose);

//  SliderStyle* st=new SliderStyle();
//  ui->slHue->setStyle(st);

  QApplication::setStyle(QStyleFactory::create("fusion"));

  ui->slHue->setStyle(new NorwegianWoodStyle);


//  QStyle s;
//  ui->slHue->setStyle();
}
