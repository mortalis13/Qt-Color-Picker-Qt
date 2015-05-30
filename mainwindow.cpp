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

  colorProcessor=new ColorProcessor();

  ui->leHSV->setTextMargins(margins);
  ui->leRGB->setTextMargins(margins);
  ui->leCMYK->setTextMargins(margins);
  ui->leHex->setTextMargins(margins);
}

void MainWindow::addActions(){
  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->satValueSelector, SLOT(changeHue(QColor)) );
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );
}

void MainWindow::updateColorText(QColor color){
  QString HSV, RGB, CMYK, Hex;
  
  HSV=colorProcessor->getHSV(color);
  RGB=colorProcessor->getRGB(color);
  CMYK=colorProcessor->getCMYK(color);
  Hex=colorProcessor->getHex(color);
  
  setHSV(HSV);
  setRGB(RGB);
  setCMYK(CMYK);
  setHex(Hex);
}

void MainWindow::setHSV(QString text){
  ui->leHSV->setText(text);
}

void MainWindow::setRGB(QString text){
  ui->leRGB->setText(text);
}

void MainWindow::setCMYK(QString text){
  ui->leCMYK->setText(text);
}

void MainWindow::setHex(QString text){
  ui->leHex->setText(text);
}
