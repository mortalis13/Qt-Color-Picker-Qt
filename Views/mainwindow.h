#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

#include <QLineEdit>

#include "Models/colorprocessor.h"

#include "Controllers/sliderscontroller.h"
#include "Controllers/maincontroller.h"

#include "sliders.h"

namespace Ui {
class MainWindow;
}

class MainController;

class MainWindow : public QMainWindow
{
  Q_OBJECT

private:
  QSignalMapper *mapper;
  
  Ui::MainWindow *ui;
  
  SlidersController *slidersController;
  MainController *mainController;
  
  ColorProcessor *colorProcessor;
  Sliders* slidersWindow;
  
  QString editingField;

  bool mouseDown;
  bool mouseMoved;
  int mx, my;
  

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void setHSV(QString text);
  void setRGB(QString text);
  void setCMYK(QString text);
  void setHex(QString text);

  QString getHSV();
  QString getRGB();
  QString getCMYK();
  QString getHex();


private:
  void addActions();
  void addShortcuts();
  void addSlidersActions();
  void init();
    
  void updateSliders();
  void stickSliders();
  void status(QString msg);

  void correctFields();
  QString correctField(QString text);
  
  
protected:
  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  

signals:
  void mouseMovedOnWindow();
  void mouseReleasedOnWindow();
  void shiftPressed();
  void shiftReleased();
  void ctrlPressed();
  void ctrlReleased();

public slots:
  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
  void updateColorCMYK(QString CMYK);
  void updateColorHex(QString Hex);

private slots:
  void selectField(QWidget* w);
  
  void updateColorText(QColor color);
  void updateColorFinished();

  void copyHSV();
  void copyRGB();
  void copyCMYK();
  void copyHex();
  void copyHexHash();
  void pasteHex();  

  void middleClick(QMouseEvent *e);
  void hsvMiddlePressed(QMouseEvent *e);
  
  void toggleSliders();
  void closeSliders();
  void openSliders();
  
  
};

#endif // MAINWINDOW_H

