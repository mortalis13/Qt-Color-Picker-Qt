#ifndef COLORTEXT_H
#define COLORTEXT_H

#include <QLineEdit>
#include <QKeyEvent>

class ColorText : public QLineEdit
{
  Q_OBJECT

public:
  enum ColorType{
    HSV, RGB, CMYK, Hex
  };

private:
  ColorType colorType;

public:
  explicit ColorText(QWidget *parent = 0);

  void setType(ColorType colorType);
signals:

public slots:

protected:
  void keyPressEvent(QKeyEvent *e);
  bool event(QEvent *e);

private:
  void increaseComponent();
  void decreaseComponent();
  void changeComponentVal(bool inc);

  bool checkVal(int val, int group);
  int getGroup();

  void selectNextComponent();
  void selectPrevComponent();
  void selectComponent(bool next);
};

#endif // COLORTEXT_H
