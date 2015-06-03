#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPainter>
#include <QPalette>

#include "Widgets/ColorWidgets/hselector.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  colorProcessor=new ColorProcessor(ui->hSelector, ui->svSelector);
  slidersWindow=new Sliders(this);

  addActions();
  addSlidersActions();
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init(){
  mx=0;
  my=0;

  QApplication::setStyle("fusion");

  QMargins margins(5,0,0,0);

  ui->leHSV->setTextMargins(margins);
  ui->leRGB->setTextMargins(margins);
  ui->leCMYK->setTextMargins(margins);
  ui->leHex->setTextMargins(margins);

  ui->leHSV->setType(Vars::HSV);
  ui->leRGB->setType(Vars::RGB);
  ui->leCMYK->setType(Vars::CMYK);
  ui->leHex->setType(Vars::Hex);
  
  ui->hSelector->setInitH(0);
}

void MainWindow::addActions(){
  connect( ui->hSelector, SIGNAL(hueChanged(QColor)), ui->svSelector, SLOT(changeHue(QColor)) );
  connect( ui->svSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  // connect( ui->svSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );

  connect( ui->leHSV, SIGNAL(textEdited(QString)), this, SLOT(updateColorHSV(QString)) );
  connect( ui->leRGB, SIGNAL(textEdited(QString)), this, SLOT(updateColorRGB(QString)) );
  connect( ui->leCMYK, SIGNAL(textEdited(QString)), this, SLOT(updateColorCMYK(QString)) );
  connect( ui->leHex, SIGNAL(textEdited(QString)), this, SLOT(updateColorHex(QString)) );
  
  connect( colorProcessor, SIGNAL(updateFinished()), this, SLOT(updateColorFinished()) );

  connect( ui->bHSV, SIGNAL(clicked()), this, SLOT(copyHSV()) );
  connect( ui->bRGB, SIGNAL(clicked()), this, SLOT(copyRGB()) );
  connect( ui->bCMYK, SIGNAL(clicked()), this, SLOT(copyCMYK()) );

  connect( ui->bHex, SIGNAL(clicked()), this, SLOT(copyHex()) );
  connect( ui->bHexHash, SIGNAL(clicked()), this, SLOT(copyHexHash()) );
  connect( ui->bPasteHex, SIGNAL(clicked()), this, SLOT(pasteHex()) );

  connect( ui->colorSample, SIGNAL(samplePressedLeft()), this, SLOT(copyHex()) );
  connect( ui->colorSample, SIGNAL(samplePressedRight()), this, SLOT(copyHexHash()) );

  connect( ui->hSelector, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(hsvMiddlePressed(QMouseEvent*)) );
  connect( ui->svSelector, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(hsvMiddlePressed(QMouseEvent*)) );

  connect( this, SIGNAL(mouseMovedOnWindow()), ui->colorSample, SLOT(mouseMovedOnWindow()) );
  connect( this, SIGNAL(shiftPressed()), ui->svSelector, SLOT(shiftPressed()) );
  connect( this, SIGNAL(shiftReleased()), ui->svSelector, SLOT(shiftReleased()) );

  connect( ui->bSliders, SIGNAL(clicked()), this, SLOT(openSliders()) );
}

void MainWindow::addSlidersActions(){
  // === HSV ===
  
  connect( slidersWindow, SIGNAL(hueChanged(QColor)), this, SLOT(changeHue(QColor)) );
  connect( slidersWindow, SIGNAL(saturationChanged(QColor)), this, SLOT(changeSaturation(QColor)) );
  connect( slidersWindow, SIGNAL(valueChanged(QColor)), this, SLOT(changeValue(QColor)) );
  
  connect( ui->hSelector, SIGNAL(hueChanged(QColor)), slidersWindow, SLOT(changeHueFromSelector(QColor)) );
  connect( ui->svSelector, SIGNAL(saturationChanged(QColor)), slidersWindow, SLOT(changeSaturationFromSelector(QColor)) );
  connect( ui->svSelector, SIGNAL(valueChanged(QColor)), slidersWindow, SLOT(changeValueFromSelector(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeHSVFromSelector(QColor)) );
  
  
  // === RGB ===
  
  connect( slidersWindow, SIGNAL(redChanged(QColor)), this, SLOT(changeRed(QColor)) );
  connect( slidersWindow, SIGNAL(greenChanged(QColor)), this, SLOT(changeGreen(QColor)) );
  connect( slidersWindow, SIGNAL(blueChanged(QColor)), this, SLOT(changeBlue(QColor)) );
  
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeRedFromSelector(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeGreenFromSelector(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeBlueFromSelector(QColor)) );
}


// --------------------------------------------- slots ---------------------------------------------

void MainWindow::hsvMiddlePressed(QMouseEvent* e){
  mouseDown=true;
  mouseMoved=false;

  mx=e->x();
  my=e->y();
}

void MainWindow::middleClick(QMouseEvent* e){
  mouseReleaseEvent(e);
}

void MainWindow::openSliders(){
  int corrX=frameGeometry().width()-width();

  int sx=x();
  int sy=y();
  int w=slidersWindow->width()+corrX;
  sx-=w;
  
  slidersWindow->move(sx, sy);
  slidersWindow->show();
}


// --------------------------------------------- HSV ---------------------------------------------

// ===== hue =====
void MainWindow::changeHue(QColor color){
  ui->hSelector->setH(color);
}

// ===== saturation =====
void MainWindow::changeSaturation(QColor color){
  ui->svSelector->setS(color);
}

// ===== value =====
void MainWindow::changeValue(QColor color){
  ui->svSelector->setV(color);
}


// --------------------------------------------- RGB ---------------------------------------------

void MainWindow::connectColorSampleRGB(){
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeRedFromSelector(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeGreenFromSelector(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, SLOT(changeBlueFromSelector(QColor)) );
}

void MainWindow::disconnectColorSampleRGB(){
  disconnect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersWindow, 0 );
}

void MainWindow::changeRGB(int pos, int val){
  QString RGB_Text=ui->leRGB->text();
  QColor currentColor=colorProcessor->getColorRGB(RGB_Text);
  
  switch(pos){
    case 0:
      currentColor.setRed(val);
      break;  
    case 1:
      currentColor.setGreen(val);
      break;  
    case 2:
      currentColor.setBlue(val);
      break;  
  }
  
  disconnectColorSampleRGB();
  QString RGB=colorProcessor->getRGB(currentColor);
  setRGB(RGB);
  updateColorRGB(RGB);
  connectColorSampleRGB();
}

// ===== red =====
void MainWindow::changeRed(QColor color){
  changeRGB(0, color.red());
}

// ===== green =====
void MainWindow::changeGreen(QColor color){
  changeRGB(1, color.green());
}

// ===== blue =====
void MainWindow::changeBlue(QColor color){
  changeRGB(2, color.blue());
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

void MainWindow::correctFields(){
  QString text;
  text=ui->leHSV->text();
  text=correctField(text);
  ui->leHSV->setText(text);
  
  text=ui->leRGB->text();
  text=correctField(text);
  ui->leRGB->setText(text);
  
  text=ui->leCMYK->text();
  text=correctField(text);
  ui->leCMYK->setText(text);
  
  text=ui->leHex->text();
  text=correctField(text);
  ui->leHex->setText(text);
}

QString MainWindow::correctField(QString text){         // +++ to Validator
  text=text.trimmed();
  text=text.replace("\\s+", " ");
    
  return text;
}

void MainWindow::status(QString msg){
  ui->statusBar->showMessage(msg, 3000);
}

// --------------------------------------------- events ---------------------------------------------

void MainWindow::mousePressEvent(QMouseEvent *e)
{
  mouseDown=true;
  mouseMoved=false;

  mx=e->x();
  my=e->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
  mouseDown=false;
  if(e->button()==Qt::MiddleButton && !mouseMoved) close();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
  if(mouseDown){
    mouseMoved=true;

    emit mouseMovedOnWindow();

    int gx=e->globalX();
    int gy=e->globalY();

    int corrX=geometry().x()-x();
    int corrY=geometry().y()-y();

    int moveX=gx-mx-corrX;
    int moveY=gy-my-corrY;

    move(moveX, moveY);
  }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  int key=e->key();
  if(key == Qt::Key_Shift){
    emit shiftPressed();
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
  int key=e->key();
  if(key == Qt::Key_Shift){
    emit shiftReleased();
  }
}
