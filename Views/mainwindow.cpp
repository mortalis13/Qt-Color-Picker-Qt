#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QShortcut>
#include <QScreen>

#include "Widgets/ColorWidgets/hselector.h"
#include "Service/validator.h"

#include "pickerview.h"
#include "testwidget.h"
#include "testdialog.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  colorProcessor = new ColorProcessor(ui->hSelector, ui->svSelector);
  mainController = new MainController(ui->hSelector, ui->svSelector, colorProcessor, this);
  
  slidersWindow = NULL;

  addActions();
  addShortcuts();
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  qDebug() << "Event Filter: " << event->type();
  return QObject::eventFilter(obj, event);
}


void MainWindow::init() {
  QApplication::setStyle("fusion");
  
  mx = 0;
  my = 0;
  
  mouseDown = false;

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
  
  // qApp->installEventFilter(this);
}

void MainWindow::addActions() {
  connect( ui->hSelector, SIGNAL(hueChanged(QColor)), ui->svSelector, SLOT(changeHue(QColor)) );
  connect( ui->svSelector, SIGNAL(colorChanged(QColor)), ui->colorSample, SLOT(changeColor(QColor)) );
  connect( ui->colorSample, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );
  // connect( ui->svSelector, SIGNAL(colorChanged(QColor)), this, SLOT(updateColorText(QColor)) );

  connect( ui->leHSV,  SIGNAL(textEdited(QString)), this, SLOT(updateColorHSV(QString)) );
  connect( ui->leRGB,  SIGNAL(textEdited(QString)), this, SLOT(updateColorRGB(QString)) );
  connect( ui->leCMYK, SIGNAL(textEdited(QString)), this, SLOT(updateColorCMYK(QString)) );
  connect( ui->leHex,  SIGNAL(textEdited(QString)), this, SLOT(updateColorHex(QString)) );
  
  connect( ui->leHSV,  SIGNAL(focusNextField()), this, SLOT(focusNextField()) );
  connect( ui->leRGB,  SIGNAL(focusNextField()), this, SLOT(focusNextField()) );
  connect( ui->leCMYK, SIGNAL(focusNextField()), this, SLOT(focusNextField()) );
  connect( ui->leHex,  SIGNAL(focusNextField()), this, SLOT(focusNextField()) );
  
  connect( ui->leHSV,  SIGNAL(focusPrevField()), this, SLOT(focusPrevField()) );
  connect( ui->leRGB,  SIGNAL(focusPrevField()), this, SLOT(focusPrevField()) );
  connect( ui->leCMYK, SIGNAL(focusPrevField()), this, SLOT(focusPrevField()) );
  connect( ui->leHex,  SIGNAL(focusPrevField()), this, SLOT(focusPrevField()) );
  
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
  
  // connect( ui->bShowPicker, SIGNAL(clicked()), this, SLOT(showPickerClicked()) );
  // connect( ui->bSliders, SIGNAL(clicked()), this, SLOT(openSliders()) );
}

void MainWindow::addSlidersActions() {
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

void MainWindow::addShortcuts() {
  QShortcut* HSV_Text = new QShortcut(QKeySequence("Shift+F1"), this);
  QShortcut* RGB_Text = new QShortcut(QKeySequence("Shift+F2"), this);
  QShortcut* CMYK_Text = new QShortcut(QKeySequence("Shift+F3"), this);
  QShortcut* Hex_Text = new QShortcut(QKeySequence("Shift+F4"), this);
  
  QShortcut* toggleSlider_Key = new QShortcut(QKeySequence("Ctrl+S"), this);
  connect( toggleSlider_Key, SIGNAL(activated()), this, SLOT(toggleSliders()) );
  
  mapper = new QSignalMapper(this);
  mapper->setMapping(HSV_Text, ui->leHSV);
  mapper->setMapping(RGB_Text, ui->leRGB);
  mapper->setMapping(CMYK_Text, ui->leCMYK);
  mapper->setMapping(Hex_Text, ui->leHex);
  
  connect( HSV_Text, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( RGB_Text, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( CMYK_Text, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( Hex_Text, SIGNAL(activated()), mapper, SLOT(map()) );
  connect( mapper, SIGNAL(mapped(QWidget*)), this, SLOT(selectField(QWidget*)) );
  
  
  QShortcut* HSV_Button = new QShortcut(QKeySequence("F1"), this);
  connect( HSV_Button, SIGNAL(activated()), ui->bHSV, SLOT(click()) );
  
  QShortcut* RGB_Button = new QShortcut(QKeySequence("F2"), this);
  connect( RGB_Button, SIGNAL(activated()), ui->bRGB, SLOT(click()) );
  
  QShortcut* CMYK_Button = new QShortcut(QKeySequence("F3"), this);
  connect( CMYK_Button, SIGNAL(activated()), ui->bCMYK, SLOT(click()) );
  
  QShortcut* Hex_Button = new QShortcut(QKeySequence("F4"), this);
  connect( Hex_Button, SIGNAL(activated()), ui->bHex, SLOT(click()) );

  QShortcut* HexHash_Button = new QShortcut(QKeySequence("F5"), this);
  connect( HexHash_Button, SIGNAL(activated()), ui->bHexHash, SLOT(click()) );

  QShortcut* PasteHex_Button = new QShortcut(QKeySequence("F6"), this);
  connect( PasteHex_Button, SIGNAL(activated()), ui->bPasteHex, SLOT(click()) );

  
  QShortcut *quit = new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}

void MainWindow::selectField(QWidget* w) {
  QLineEdit* field = (QLineEdit*) w;
  field->setFocus();
  field->selectAll();
}


// --------------------------------------------- slots ---------------------------------------------

void MainWindow::hsvMiddlePressed(QMouseEvent* e) {
  mouseDown = true;
  mouseMoved = false;

  mx = e->x();
  my = e->y();
}

void MainWindow::middleClick(QMouseEvent* e) {
  mouseReleaseEvent(e);
}

void MainWindow::updateSliders() {
  ui->hSelector->reupdateColor();
  ui->svSelector->reupdateColor();
  ui->colorSample->reupdateColor();
}

void MainWindow::toggleSliders() {
  if (slidersWindow==NULL || !slidersWindow->isVisible())
    openSliders();
  else
    closeSliders();
}

void MainWindow::closeSliders() {
  slidersWindow->hide();
}

void MainWindow::openSliders() {
  if (slidersWindow==NULL) {
    slidersController = new SlidersController();
    slidersWindow = new SlidersWindow(slidersController, this);
    
    slidersController->setView(slidersWindow);
    mainController->addSlidersController(slidersController);
    
    addSlidersActions();
    updateSliders();
  }
  
  if (slidersWindow!=NULL) {
    stickSliders();
    slidersWindow->show();
  }
}

void MainWindow::stickSliders() {
  int corrX = frameGeometry().width()-width();

  int sx = x();
  int sy = y();
  int w = slidersWindow->width()+corrX;
  sx-=w;
  
  // qDebug() << QString("Sliders: %1, %2").arg(sx).arg(sy);
  
  sx = qMax(0, sx);
  
  slidersWindow->move(sx, sy);
}


void MainWindow::focusNextField() {
  if (ui->leHSV->hasFocus()) {
    ui->leRGB->setFocus(Qt::TabFocusReason);
  }
  else if (ui->leRGB->hasFocus()) {
    ui->leCMYK->setFocus(Qt::TabFocusReason);
  }
  else if (ui->leCMYK->hasFocus()) {
    ui->leHex->setFocus(Qt::TabFocusReason);
  }
  else if (ui->leHex->hasFocus()) {
    ui->leHSV->setFocus(Qt::TabFocusReason);
  }
}

void MainWindow::focusPrevField() {
  if (ui->leHSV->hasFocus()) {
    ui->leHex->setFocus(Qt::BacktabFocusReason);
  }
  else if (ui->leHex->hasFocus()) {
    ui->leCMYK->setFocus(Qt::BacktabFocusReason);
  }
  else if (ui->leCMYK->hasFocus()) {
    ui->leRGB->setFocus(Qt::BacktabFocusReason);
  }
  else if (ui->leRGB->hasFocus()) {
    ui->leHSV->setFocus(Qt::BacktabFocusReason);
  }
}

void MainWindow::showPickerClicked() {
  // PickerView* w = new PickerView(this);
  TestWidget* w = new TestWidget(this);
  // TestWidget* w = new TestWidget;
  // TestDialog* w = new TestDialog(this);
  
  w->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  
  QPoint pos = QCursor::pos();
  int wx = pos.x() - w->width()/2;
  int wy = pos.y() - w->height()/2;
  
  // w->move(10, 10);
  w->move(wx, wy);
  w->show();
  
  // w->grabMouse();
}


// --------------------------------------------- buttons ---------------------------------------------

void MainWindow::copyHSV() {
  QString text = ui->leHSV->text();
  text = text.replace(" ", ", ");
  colorProcessor->copyText(text);
  status("HSV copied");
}

void MainWindow::copyRGB() {
  QString text = ui->leRGB->text();
  text = text.replace(" ", ", ");
  colorProcessor->copyText(text);
  status("RGB copied");
}

void MainWindow::copyCMYK() {
  QString text = ui->leCMYK->text();
  text = text.replace(" ", ", ");
  colorProcessor->copyText(text);
  status("CMYK copied");
}

void MainWindow::copyHex() {
  QString text = ui->leHex->text();
  colorProcessor->copyText(text);
  status("Hex copied");
}

void MainWindow::copyHexHash() {
  QString text = ui->leHex->text();
  colorProcessor->copyText("#"+text);
  status("Hex # copied");
}

void MainWindow::pasteHex() {
  QString text = colorProcessor->pasteText();
  if (!text.length()) return;

  ui->leHex->setText(text);
  ui->leHex->textEdited(text);
  status("Hex value pasted");
}

// --------------------------------------------- update color ---------------------------------------------

void MainWindow::updateColorFinished() {
  editingField = "";
}

void MainWindow::updateColorHSV(QString text) {
  editingField = "HSV";
  text = Validator::correctColorText(text);
  ui->leHSV->updateText(text);
  colorProcessor->updateColorHSV(text);
}

void MainWindow::updateColorRGB(QString text) {
  editingField = "RGB";
  text = Validator::correctColorText(text);
  ui->leRGB->updateText(text);
  colorProcessor->updateColorRGB(text);
}

void MainWindow::updateColorCMYK(QString text) {
  editingField = "CMYK";
  text = Validator::correctColorText(text);
  ui->leCMYK->updateText(text);
  colorProcessor->updateColorCMYK(text);
}

void MainWindow::updateColorHex(QString text) {
  editingField = "Hex";
  text = Validator::correctColorText(text);
  ui->leHex->updateText(text);
  colorProcessor->updateColorHex(text);
}

// --------------------------------------------- update color text ---------------------------------------------

void MainWindow::updateColorText(QColor color) {
  QString HSV, RGB, CMYK, Hex;
  
  HSV = colorProcessor->getHSV(color);
  RGB = colorProcessor->getRGB(color);
  CMYK = colorProcessor->getCMYK(color);
  Hex = colorProcessor->getHex(color);
  
  setHSV(HSV);
  setRGB(RGB);
  setCMYK(CMYK);
  setHex(Hex);
}

void MainWindow::setHSV(QString text) {
  if (editingField=="HSV") return;
  ui->leHSV->setText(text);
}

void MainWindow::setRGB(QString text) {
  if (editingField=="RGB") return;
  ui->leRGB->setText(text);
}

void MainWindow::setCMYK(QString text) {
  if (editingField=="CMYK") return;
  ui->leCMYK->setText(text);
}

void MainWindow::setHex(QString text) {
  if (editingField=="Hex") return;
  ui->leHex->setText(text);
}


QString MainWindow::getHSV() {
  return ui->leHSV->text();
}

QString MainWindow::getRGB() {
  return ui->leRGB->text();
}

QString MainWindow::getCMYK() {
  return ui->leCMYK->text();
}

QString MainWindow::getHex() {
  return ui->leHex->text();
}

// --------------------------------------------- service ---------------------------------------------

void MainWindow::correctFields() {
  QString text;
  text = ui->leHSV->text();
  text = correctField(text);
  ui->leHSV->setText(text);
  
  text = ui->leRGB->text();
  text = correctField(text);
  ui->leRGB->setText(text);
  
  text = ui->leCMYK->text();
  text = correctField(text);
  ui->leCMYK->setText(text);
  
  text = ui->leHex->text();
  text = correctField(text);
  ui->leHex->setText(text);
}

QString MainWindow::correctField(QString text) {         // +++ to Validator
  text = text.trimmed();
  text = text.replace(QRegExp("\\s+"), " ");
    
  return text;
}

void MainWindow::status(QString msg) {
  ui->statusBar->showMessage(msg, 3000);
}

// --------------------------------------------- events ---------------------------------------------

void MainWindow::mousePressEvent(QMouseEvent *e)
{
  mouseDown = true;
  mouseMoved = false;

  mx = e->x();
  my = e->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
  mouseDown = false;
  if (e->button()==Qt::MiddleButton && !mouseMoved) close();
  emit mouseReleasedOnWindow();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
  if (mouseDown) {
    mouseMoved = true;

    emit mouseMovedOnWindow();

    int gx = e->globalX();
    int gy = e->globalY();

    int corrX = geometry().x()-x();
    int corrY = geometry().y()-y();

    int moveX = gx-mx-corrX;
    int moveY = gy-my-corrY;

    move(moveX, moveY);
  }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  int key = e->key();
  if (key == Qt::Key_Shift) {
    emit shiftPressed();
  }
  if (key == Qt::Key_Control) {
    emit ctrlPressed();
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
  int key = e->key();
  if (key == Qt::Key_Shift) {
    emit shiftReleased();
  }
  if (key == Qt::Key_Control) {
    emit ctrlReleased();
  }
}
