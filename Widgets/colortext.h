#ifndef COLORTEXT_H
#define COLORTEXT_H

#include <QLineEdit>
#include <QKeyEvent>

#include "Service/vars.h"

class ColorText : public QLineEdit
{
  Q_OBJECT

private:
  Vars::ColorType colorType;
  QString separator;
  int len;

public:
  explicit ColorText(QWidget *parent = 0);

  void setType(Vars::ColorType colorType);
  void updateText(QString text);
  
signals:
  void focusNextField();
  void focusPrevField();
  

public slots:

protected:
  void keyPressEvent(QKeyEvent *e);
  void wheelEvent(QWheelEvent *e);
  bool event(QEvent *e);

private:
  void changeComponentVal(int pos, bool inc);

  int getGroup();

  void selectNextComponent();
  void selectPrevComponent();
  void selectComponent(bool next);
  QStringList getComponentsFromHex(QString hex);
  int getGroupNumber(int group, int groupLen, bool next);
  int getHexGroup(int pos, int len);
  bool checkValueHex(QString text);
  
};

#endif // COLORTEXT_H
