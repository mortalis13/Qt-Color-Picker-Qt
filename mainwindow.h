#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "colorprocessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

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

private:
  Ui::MainWindow *ui;
  ColorProcessor *colorProcessor;
  QString editingField;

  void addActions();
  void init();
  
  void setHSV(QString text);
  void setRGB(QString text);
  void setCMYK(QString text);
  void setHex(QString text);
  
  void status(QString msg);

  bool mouseDown;
  int mx, my;

protected:
  void mouseMoveEvent(QMouseEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);

};

#endif // MAINWINDOW_H

