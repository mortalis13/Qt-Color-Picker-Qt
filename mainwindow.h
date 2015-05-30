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

  void updateColorHSV(QString HSV);
  void updateColorRGB(QString RGB);
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
  
};

#endif // MAINWINDOW_H

