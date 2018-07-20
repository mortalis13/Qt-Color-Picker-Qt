#include "testwidget.h"
#include "ui_testwidget.h"


#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QScreen>


TestWidget::TestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TestWidget)
{
  ui->setupUi(this);
}

TestWidget::~TestWidget()
{
  delete ui;
}


void TestWidget::paintEvent(QPaintEvent *event) {
  int w = width();
  int h = height();
  
  QPainter p(this);
  
  int b = 2;
  int step = 10;
  
  // -- setup
  QPen pen;
  pen.setWidth(b);
  pen.setColor(QColor(40,40,40));
  pen.setJoinStyle(Qt::RoundJoin);
  
  // p.setRenderHint(QPainter::Antialiasing);
  p.setPen(pen);
  p.setBrush(QBrush(QColor(255,255,255)));
  
  QPen penGrid;
  penGrid.setWidth(1);
  penGrid.setColor(QColor(0,0,0));
  
  // -- draw
  p.drawRect(b/2, b/2, w-b, h-b);
  p.setPen(penGrid);
  
  int cols = (w - 2*b) / step;
  int rows = (h - 2*b) / step;
  
  for (int i = 1; i < cols; i++) {
    int x = b/2 + i*(step+1);
    p.drawLine(x, b, x, h-b);
  }
  
  for (int i = 1; i < rows; i++) {
    int y = b/2 + i*(step+1);
    p.drawLine(b, y, w-b, y);
  }
  
  
  // -- screen pixels
  QPixmap pix = QPixmap();
  QScreen *screen = QGuiApplication::primaryScreen();
  if (screen) pix = screen->grabWindow(0);
  
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      QRgb rgb = pix.toImage().pixel(row, col);
      QColor pixColor(rgb);
      p.setPen(QPen(pixColor));
      
      for (int k = 0; k < step*step; k++) {
        int x = col * step + k % step;
        int y = row * step + k / step;
        if (x == col*step || y == row*step) continue;
        if (x < b || y < b) continue;
        if (x >= w-b || y >= h-b) continue;
        p.drawPoint(x, y);
      }
    }
  }
}

void TestWidget::mousePressEvent(QMouseEvent *e)
{
  mx=e->x();
  my=e->y();
}

void TestWidget::mouseMoveEvent(QMouseEvent *e) {
  // int x = e->x();
  // int y = e->y();
  
  // int wx = x - width()/2;
  // int wy = y - height()/2;
  
  // // qDebug() << wx << wy;
  // move(wx, wy);
  
  
  int gx=e->globalX();
  int gy=e->globalY();

  int corrX=geometry().x() - x();
  int corrY=geometry().y() - y();

  int moveX=gx-mx-corrX;
  int moveY=gy-my-corrY;

  move(moveX, moveY);
}

