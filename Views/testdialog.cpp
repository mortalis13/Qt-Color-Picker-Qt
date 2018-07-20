#include "testdialog.h"
#include "ui_testdialog.h"

#include <QPainter>
#include <QMouseEvent>

TestDialog::TestDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TestDialog)
{
  ui->setupUi(this);
}

TestDialog::~TestDialog()
{
  delete ui;
}


void TestDialog::paintEvent(QPaintEvent *event)
{
  int w = width();
  int h = height();
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  QPen pen;
  pen.setWidth(2);
  pen.setColor(QColor(40,40,40,255));
  
  p.setPen(pen);
  p.setBrush(QBrush(QColor(0,0,0)));
  
  p.drawRect(0, 0, w, h);
}

