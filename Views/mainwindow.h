#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Models/colorprocessor.h"
//#include "sliders.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void addActions();
  void init();
  
  void setHSV(QString text);
  void setRGB(QString text);
  void setCMYK(QString text);
  void setHex(QString text);
  
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
//  Sliders* slidersWindow;

  bool mouseDown;
  bool mouseMoved;
  int mx, my;
  

signals:
  void mouseMovedOnWindow();
  void shiftPressed();
  void shiftReleased();

private slots:
  void updateColorText(QColor color);
  void updateColorFinished();

  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
  void updateColorCMYK(QString CMYK);
  void updateColorHex(QString Hex);
  
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

