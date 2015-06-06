#include <QApplication>
#include <QDesktopWidget>

#include "Views/mainwindow.h"


void setPosition(MainWindow &view){
  QDesktopWidget *w=QApplication::desktop();
  int primary=w->primaryScreen();
  QRect dim=w->screenGeometry(primary);

  int mx,my, corr=20;

  mx=view.x();
  mx=dim.width() - view.width() - corr;
  my=corr;

  view.move(mx, my);
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow view;

  view.show();
  setPosition(view);

  return a.exec();
}


// void saveHuesToFile(){
//   QFile file("hues.dat");
//   if( !file.open(QIODevice::WriteOnly) ){
//     qDebug("Cannot open file");
//     return;
//   }

//   QList<QImage> hues;
//   QColor color;

//   int maxHue=360;
//   int max=255;

//   for(int h=0;h<maxHue;h++){
//     QImage image(max+1, max+1, QImage::Format_RGB32);

//     for(int s=0; s<=max; s++){
//       for(int v=0; v<=max; v++){
//         color.setHsv(h, s, v);
//         image.setPixel(s, max-v, color.rgb());
//       }
//     }

//     hues.append(image);
//   }

//   QDataStream stream(&file);
//   stream << hues;
//   file.close();
// }
