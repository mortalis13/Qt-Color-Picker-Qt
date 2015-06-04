#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QShortcut>

#include "Widgets/ColorWidgets/hselector.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  colorProcessor=new ColorProcessor(ui->hSelector, ui->svSelector);
  mainController=new MainController(ui->hSelector, ui->svSelector, colorProcessor, this);
  
  slidersWindow=NULL;

  addActions();
  addShortcuts();
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init(){
  QApplication::setStyle("fusion");
  
  mx=0;
  my=0;
  
  mouseDown=false;

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
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );
  // connect( ui->svSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );

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
  connect( ui->colorSample, SIGNAL(samplePressedMiddle()), this, SLOT(toggleSliders()) );

  connect( ui->hSelector, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(hsvMiddlePressed(QMouseEvent*)) );
  connect( ui->svSelector, SIGNAL(middlePressedSignal(QMouseEvent*)), this, SLOT(hsvMiddlePressed(QMouseEvent*)) );

  connect( this, SIGNAL(mouseMovedOnWindow()), ui->colorSample, SLOT(mouseMovedOnWindow()) );
  connect( this, SIGNAL(mouseReleasedOnWindow()), ui->colorSample, SLOT(mouseReleasedOnWindow()) );
  connect( this, SIGNAL(shiftPressed()), ui->svSelector, SLOT(shiftPressed()) );
  connect( this, SIGNAL(shiftReleased()), ui->svSelector, SLOT(shiftReleased()) );
  
  connect( this, SIGNAL(ctrlPressed()), ui->svSelector, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->svSelector, SLOT(ctrlReleased()) );
  connect( this, SIGNAL(ctrlPressed()), ui->hSelector, SLOT(ctrlPressed()) );
  connect( this, SIGNAL(ctrlReleased()), ui->hSelector, SLOT(ctrlReleased()) );

  // connect( ui->bSliders, SIGNAL(clicked()), this, SLOT(openSliders()) );
}

void MainWindow::addSlidersActions(){
  // === HSV ===
  
  connect( slidersController, SIGNAL(hueChanged(QColor)), mainController, SLOT(changeHue(QColor)) );
  connect( slidersController, SIGNAL(saturationChanged(QColor)), mainController, SLOT(changeSaturation(QColor)) );
  connect( slidersController, SIGNAL(valueChanged(QColor)), mainController, SLOT(changeValue(QColor)) );
  
  connect( ui->hSelector, SIGNAL(hueChanged(QColor)), slidersController, SLOT(changeHueFromSelector(QColor)) );
  connect( ui->svSelector, SIGNAL(saturationChanged(QColor)), slidersController, SLOT(changeSaturationFromSelector(QColor)) );
  connect( ui->svSelector, SIGNAL(valueChanged(QColor)), slidersController, SLOT(changeValueFromSelector(QColor)) );
  
  
  // === RGB ===
  
  connect( slidersController, SIGNAL(redChanged(QColor)), mainController, SLOT(changeRed(QColor)) );
  connect( slidersController, SIGNAL(greenChanged(QColor)), mainController, SLOT(changeGreen(QColor)) );
  connect( slidersController, SIGNAL(blueChanged(QColor)), mainController, SLOT(changeBlue(QColor)) );
  
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersController, SIGNAL(RGBChanged(QColor)) );
  
  
  // === CMYK ===
  
  connect( slidersController, SIGNAL(cyanChanged(QColor)), mainController, SLOT(changeCyan(QColor)) );
  connect( slidersController, SIGNAL(magentaChanged(QColor)), mainController, SLOT(changeMagenta(QColor)) );
  connect( slidersController, SIGNAL(yellowChanged(QColor)), mainController, SLOT(changeYellow(QColor)) );
  connect( slidersController, SIGNAL(blackChanged(QColor)), mainController, SLOT(changeBlack(QColor)) );
  
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), slidersController, SIGNAL(CMYKChanged(QColor)) );
}

void MainWindow::addShortcuts(){
  QShortcut* HSV=new QShortcut(QKeySequence("Ctrl+H"), this);
  QShortcut* RGB=new QShortcut(QKeySequence("Ctrl+R"), this);
  QShortcut* CMYK=new QShortcut(QKeySequence("Ctrl+M"), this);
  QShortcut* Hex=new QShortcut(QKeySequence("Ctrl+E"), this);
  
  mapper=new QSignalMapper(this);
  mapper->setMapping(HSV, ui->leHSV);
  mapper->setMapping(RGB, ui->leRGB);
  mapper->setMapping(CMYK, ui->leCMYK);
  mapper->setMapping(Hex, ui->leHex);
  
  connect( HSV, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( RGB, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( CMYK, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( Hex, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( mapper, SIGNAL(mapped(QWidget*)), this, SLOT(selectField(QWidget*)) );
  
  
  QShortcut* HSV_Button=new QShortcut(QKeySequence("Ctrl+Shift+H"), this);
  connect( HSV_Button, SIGNAL(activated()), ui->bHSV, SLOT(click()) );
  
  QShortcut* RGB_Button=new QShortcut(QKeySequence("Ctrl+Shift+R"), this);
  connect( RGB_Button, SIGNAL(activated()), ui->bRGB, SLOT(click()) );
  
  QShortcut* CMYK_Button=new QShortcut(QKeySequence("Ctrl+Shift+M"), this);
  connect( CMYK_Button, SIGNAL(activated()), ui->bCMYK, SLOT(click()) );
  
  QShortcut* Hex_Button=new QShortcut(QKeySequence("Ctrl+Shift+E"), this);
  connect( Hex_Button, SIGNAL(activated()), ui->bHex, SLOT(click()) );

  
  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}

void MainWindow::selectField(QWidget* w){
  QLineEdit* field=(QLineEdit*) w;
  field->setFocus();
  field->selectAll();
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

void MainWindow::updateSliders(){
  ui->hSelector->reupdateColor();
  ui->svSelector->reupdateColor();
  ui->colorSample->reupdateColor();
}

void MainWindow::stickSliders(){
  int corrX=frameGeometry().width()-width();

  int sx=x();
  int sy=y();
  int w=slidersWindow->width()+corrX;
  sx-=w;
  
  slidersWindow->move(sx, sy);
  slidersWindow->show();
}

void MainWindow::toggleSliders(){
  if(slidersWindow==NULL || !slidersWindow->isVisible())
    openSliders();
  else
    closeSliders();
}

void MainWindow::closeSliders(){
  slidersWindow->hide();
}

void MainWindow::openSliders(){
  if(slidersWindow==NULL){
    slidersController=new SlidersController();
    slidersWindow=new Sliders(slidersController, this);
    
    slidersController->setView(slidersWindow);
    mainController->addSlidersController(slidersController);
    
    addSlidersActions();
    updateSliders();
  }
  
  if(slidersWindow!=NULL)
    stickSliders();
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


QString MainWindow::getHSV(){
  return ui->leHSV->text();
}

QString MainWindow::getRGB(){
  return ui->leRGB->text();
}

QString MainWindow::getCMYK(){
  return ui->leCMYK->text();
}

QString MainWindow::getHex(){
  return ui->leHex->text();
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
  emit mouseReleasedOnWindow();
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
  if(key == Qt::Key_Control){
    emit ctrlPressed();
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
  int key=e->key();
  if(key == Qt::Key_Shift){
    emit shiftReleased();
  }
  if(key == Qt::Key_Control){
    emit ctrlReleased();
  }
}
