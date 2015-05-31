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
  colorProcessor=new ColorProcessor(ui->hueBar, ui->satValueSelector);

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

  ui->leHSV->setTextMargins(margins);
  ui->leRGB->setTextMargins(margins);
  ui->leCMYK->setTextMargins(margins);
  ui->leHex->setTextMargins(margins);

  ui->leHSV->setType(ColorText::HSV);
  ui->leRGB->setType(ColorText::RGB);
  ui->leCMYK->setType(ColorText::CMYK);
  ui->leHex->setType(ColorText::Hex);

  ui->hueBar->setH(0);
}

void MainWindow::addActions(){
  connect( ui->hueBar, SIGNAL(hueChanged(QColor)), ui->satValueSelector, SLOT(changeHue(QColor)) );

  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  connect( ui->satValueSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );

  connect( ui->leHSV, SIGNAL(textEdited(QString)), this, SLOT(updateColorHSV(QString)) );
  connect( ui->leRGB, SIGNAL(textEdited(QString)), this, SLOT(updateColorRGB(QString)) );
  connect( ui->leCMYK, SIGNAL(textEdited(QString)), this, SLOT(updateColorCMYK(QString)) );
  connect( ui->leHex, SIGNAL(textEdited(QString)), this, SLOT(updateColorHex(QString)) );
  
  connect( colorProcessor, SIGNAL(updateFinished()), this, SLOT(updateColorFinished()) );

  connect ( ui->bHSV, SIGNAL(clicked()), this, SLOT(copyHSV()) );
  connect ( ui->bRGB, SIGNAL(clicked()), this, SLOT(copyRGB()) );
  connect ( ui->bCMYK, SIGNAL(clicked()), this, SLOT(copyCMYK()) );
  connect ( ui->bHex, SIGNAL(clicked()), this, SLOT(copyHex()) );
  connect ( ui->bHexHash, SIGNAL(clicked()), this, SLOT(copyHexHash()) );

  connect ( ui->bPasteHex, SIGNAL(clicked()), this, SLOT(pasteHex()) );
}

// --------------------------------------------- buttons ---------------------------------------------

void MainWindow::copyHSV(){
  QString text=ui->leHSV->text();
  colorProcessor->copyText(text);
  status("HSV copied");
}

void MainWindow::copyRGB(){
  QString text=ui->leRGB->text();
  colorProcessor->copyText(text);
  status("RGB copied");
}

void MainWindow::copyCMYK(){
  QString text=ui->leCMYK->text();
  colorProcessor->copyText(text);
  status("CMYK copied");
}

void MainWindow::copyHex(){
  QString text=ui->leHex->text();
  colorProcessor->copyText(text);
  status("Hex copied");
}

void MainWindow::copyHexHash(){
  QString text=ui->leHex->text();
  colorProcessor->copyText("#"+text);
  status("Hex # copied");
}

void MainWindow::pasteHex(){
  QString text=colorProcessor->pasteText();
  if(!text.length()) return;
  
  ui->leHex->setText(text);
  ui->leHex->textEdited(text);
  status("Hex value pasted");
}

// --------------------------------------------- update color ---------------------------------------------

void MainWindow::updateColorFinished(){
  editingField="";
}

void MainWindow::updateColorHSV(QString HSV){
  editingField="HSV";
  colorProcessor->updateColorHSV(HSV);
}

void MainWindow::updateColorRGB(QString RGB){
  editingField="RGB";
  colorProcessor->updateColorRGB(RGB);
}

void MainWindow::updateColorCMYK(QString CMYK){
  editingField="CMYK";
  colorProcessor->updateColorCMYK(CMYK);
}

void MainWindow::updateColorHex(QString Hex){
  editingField="Hex";
  colorProcessor->updateColorHex(Hex);
}

// --------------------------------------------- update color text ---------------------------------------------

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
  if(editingField=="HSV") return;
  ui->leHSV->setText(text);
}

void MainWindow::setRGB(QString text){
  if(editingField=="RGB") return;
  ui->leRGB->setText(text);
}

void MainWindow::setCMYK(QString text){
  if(editingField=="CMYK") return;
  ui->leCMYK->setText(text);
}

void MainWindow::setHex(QString text){
  if(editingField=="Hex") return;
  ui->leHex->setText(text);
}

// --------------------------------------------- service ---------------------------------------------

void MainWindow::status(QString msg){
  ui->statusBar->showMessage(msg, 3000);
}

// --------------------------------------------- mouse drag ---------------------------------------------

void MainWindow::mousePressEvent(QMouseEvent *e)
{
  mouseDown=true;
  mx=e->x();
  my=e->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
  mouseDown=false;
  if(e->button()==Qt::MiddleButton) close();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
  if(mouseDown){
    int gx=e->globalX();
    int gy=e->globalY();

    int corrX=geometry().x()-x();
    int corrY=geometry().y()-y();

    move(gx-mx-corrX, gy-my-corrY);
  }
}
