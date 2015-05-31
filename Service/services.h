#ifndef SERVICES_H
#define SERVICES_H

#include <QObject>
#include <QPainter>

class Services : public QObject
{
  Q_OBJECT
public:
  explicit Services(QObject *parent = 0);

  static void drawRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);
  static void drawInnerRoundRect(QPainter& p, QRectF sizeRect, int borderSize, int borderRadius, QColor borderColor);

signals:

public slots:

};

#endif // SERVICES_H
