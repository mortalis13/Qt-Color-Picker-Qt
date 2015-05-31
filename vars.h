#ifndef VARS_H
#define VARS_H

#include <QObject>

class Vars : public QObject
{
  Q_OBJECT

public:
  enum ColorType{
    HSV, RGB, CMYK, Hex
  };

public:
  explicit Vars(QObject *parent = 0);

signals:

public slots:

};

#endif // VARS_H
