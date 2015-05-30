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
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init(){
//  ui->statusBar->showMessage("Hex value copied");
  QMargins margins(5,0,0,0);

  colorProcessor=new ColorProcessor(ui->hueBar, ui->satValueSelector);

  ui->leHSV->setTextMargins(margins);
  ui->leRGB->setTextMargins(margins);
  ui->leCMYK->setTextMargins(margins);
  ui->leHex->setTextMargins(margins);

  ui->hueBar->setHue(0);
}

void MainWindow::addActions(){
  connect( ui->hueBar, SIGNAL(hueChangedManually(QColor)), ui->satValueSelector, SLOT(changeHueManually(QColor)) );
  connect( ui->hueBar, SIGNAL(hueChangedFromText(QColor)), ui->satValueSelector, SLOT(changeHueFromText(QColor)) );

  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );

  connect( ui->leHSV, SIGNAL(textEdited(QString)), this, SLOT(updateColorHSV(QString)) );
  connect( ui->leRGB, SIGNAL(textEdited(QString)), this, SLOT(updateColorRGB(QString)) );
}

void MainWindow::updateColorHSV(QString HSV){
  editingField="HSV";
  colorProcessor->updateColorHSV(HSV);
}

void MainWindow::updateColorRGB(QString RGB){
  editingField="RGB";
  colorProcessor->updateColorRGB(RGB);
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
  if(editingField=="HSV"){
    editingField="";
    return;
  }
  ui->leHSV->setText(text);
}

void MainWindow::setRGB(QString text){
  if(editingField=="RGB"){
    editingField="";
    return;
  }
  ui->leRGB->setText(text);
}

void MainWindow::setCMYK(QString text){
  ui->leCMYK->setText(text);
}

void MainWindow::setHex(QString text){
  ui->leHex->setText(text);
}
