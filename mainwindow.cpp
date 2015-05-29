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
//  ui->statusBar->showMessage("Hex value copied");
  QMargins margins(5,0,0,0);

  ui->leHSV->setTextMargins(margins);
  ui->leRGB->setTextMargins(margins);
  ui->leCMYK->setTextMargins(margins);
  ui->leHex->setTextMargins(margins);
}

void MainWindow::addActions(){
  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->satValueSelector, SLOT(changeHue(QColor)) );
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
}
