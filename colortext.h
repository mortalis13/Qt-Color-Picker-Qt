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
  int len;

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

  bool checkVal(int val, int group=0, int hexLen=0);
  int getGroup();

  void selectNextComponent();
  void selectPrevComponent();
  void selectComponent(bool next);
  QStringList getComponentsFromHex(QString hex);
  int getGroupNumber(int group, int groupLen, bool next);
  int getHexGroup(int pos, int len);
};

#endif // COLORTEXT_H
