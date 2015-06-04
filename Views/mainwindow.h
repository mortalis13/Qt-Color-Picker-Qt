#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Models/colorprocessor.h"
#include "Models/colormodel.h"
#include "Models/sliderscolormodel.h"

#include "Controllers/sliderscontroller.h"

#include "sliders.h"

namespace Ui {
class MainWindow;
}

class ColorModel;
class SlidersColorModel;

class MainWindow : public QMainWindow
{
  Q_OBJECT

private:
  SlidersColorModel *slidersColorModel;
  SlidersController *slidersController;

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

  void connectColorSampleRGB();
  void disconnectColorSampleRGB();
  // void changeRGB(int pos, int val);

  void connectColorSampleCMYK();
  void disconnectColorSampleCMYK();
  // void changeCMYK(int pos, int val);


private:
  void addActions();
  void addSlidersActions();
  void init();
    
  void status(QString msg);

  void correctFields();
  QString correctField(QString text);
  
  
protected:
  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  
private:
  Ui::MainWindow *ui;
  QString editingField;

  ColorProcessor *colorProcessor;
  ColorModel *colorModel;
  Sliders* slidersWindow;

  bool mouseDown;
  bool mouseMoved;
  int mx, my;
  

signals:
  void mouseMovedOnWindow();
  void shiftPressed();
  void shiftReleased();

public slots:
  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
  void updateColorCMYK(QString CMYK);
  void updateColorHex(QString Hex);

private slots:
//  void changeHue(QColor color);
//  void changeSaturation(QColor color);
//  void changeValue(QColor color);
  
//  void changeRed(QColor color);
//  void changeGreen(QColor color);
//  void changeBlue(QColor color);
  
//  void changeCyan(QColor color);
//  void changeMagenta(QColor color);
//  void changeYellow(QColor color);
//  void changeBlack(QColor color);
  
  
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
  void openSliders();
};

#endif // MAINWINDOW_H

