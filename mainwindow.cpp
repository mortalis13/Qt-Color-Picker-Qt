#include "huebar.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  init();
  addActions();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init(){
}

void MainWindow::addActions(){
  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->satValueSelector, SLOT(changeHue(QColor)) );
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );

  connect( ui->doubleSpinBox, SIGNAL(valueChanged(double)), ui->hueBar, SLOT(changePointerSize(double)) );
}
