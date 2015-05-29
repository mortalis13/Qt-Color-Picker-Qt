#include "mainwindow.h"
#include <QApplication>

#include <QImage>
#include <QList>
#include <QFile>

void test(){
  QFile file("hues.dat");
  if( !file.open(QIODevice::WriteOnly) ){
    qDebug("Cannot open file");
    return;
  }

  QList<QImage> hues;
  QColor color;
  int size=255;
  int maxCoordinate=size-1;

  for(int h=0;h<360;h++){
    QImage image(size, size, QImage::Format_RGB32);

    for(int s=0; s<255; s++){
      for(int v=0; v<255; v++){
        color.setHsv(h, s, v);
        image.setPixel(s, maxCoordinate-v, color.rgb());
      }
    }

    hues.append(image);
  }

  QDataStream stream(&file);
  stream << hues;
  file.close();
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

//  test();

  return a.exec();
}
