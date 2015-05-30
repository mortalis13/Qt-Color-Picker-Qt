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
  QString separator;

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
  QStringList getComponentsFromHex(QString hex);
  int getGroupNumber(int group, int len, bool next);
  int getHexGroup(int pos);
};

#endif // COLORTEXT_H
