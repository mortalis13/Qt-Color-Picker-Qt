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

  addActions();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::addActions(){
//  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->satValueSelector, SLOT(changeHue(QColor)) );
}

void MainWindow::changeColorSample(QColor color){

}

void MainWindow::on_pushButton_clicked()
{
}
