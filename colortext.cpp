#include "colortext.h"

#include <QDebug>


const int minH=0;
const int maxH=360;
const int minS=0;
const int maxS=255;
const int minV=0;
const int maxV=255;

const int minRGB=0;
const int maxRGB=255;

const int minC=0;
const int maxC=255;
const int minM=0;
const int maxM=255;
const int minY=0;
const int maxY=255;
const int minK=0;
const int maxK=255;

const int minHex=0;
const int maxHex=255;


ColorText::ColorText(QWidget *parent) : QLineEdit(parent)
{
}

void ColorText::setType(ColorText::ColorType colorType)
{
  this->colorType=colorType;
}


bool ColorText::checkVal(int val, int group){

  if(colorType==HSV){
    switch(group){
    case 0:
      return (val>=minH && val<=maxH);
      break;
    case 1:
      return (val>=minS && val<=maxS);
      break;
    case 2:
      return (val>=minV && val<=maxV);
      break;
    }
  }

  if(colorType==RGB){
    return (val>=minRGB && val<=maxRGB);
  }

  if(colorType==CMYK){
    switch(group){
    case 0:
      return (val>=minC && val<=maxC);
      break;
    case 1:
      return (val>=minM && val<=maxM);
      break;
    case 2:
      return (val>=minY && val<=maxY);
      break;
    case 3:
      return (val>=minK && val<=maxK);
      break;
    }
  }

  if(colorType==Hex){
    return (val>=minHex && val<=maxHex);
  }

}

// --------------------------------------------- inc/dec component ---------------------------------------------

void ColorText::increaseComponent(){
  changeComponentVal(true);
}

void ColorText::decreaseComponent(){
  changeComponentVal(false);
}

void ColorText::changeComponentVal(bool inc){
  int val;
  QString valText, newValText;

  int pos=cursorPosition();
  QString colorText=text();
  QStringList comp=colorText.split(" ");

  QRegExp rx(" ");
  int idx=0;
  int group=-1;

  while( (idx = rx.indexIn(colorText, idx)) != -1 ){
    group++;
    if(idx>=pos) break;
    idx+=rx.matchedLength();
  }
  if(idx==-1) group=comp.size()-1;
  if(group==-1) return;

  valText=comp[group];
  val=valText.toInt();

  if(inc) val++;                                                        // ---
  else val--;
  if( !checkVal(val, group) ) return;

  newValText=QString::number(val);

  pos = (idx==-1) ? colorText.length() : idx;
  if(inc){
    if( newValText.length() > valText.length() ) pos++;           // ---
  }
  else{
    if( newValText.length() < valText.length() ) pos--;           // ---
  }

  comp[group]=newValText;
  colorText=comp.join(" ");

  setText(colorText);
  setCursorPosition(pos);

  textEdited(text());
}

// --------------------------------------------- select component ---------------------------------------------

void ColorText::selectNextComponent(){
  selectComponent(true);
}

void ColorText::selectPrevComponent(){
  selectComponent(false);
}

void ColorText::selectComponent(bool next){
  int pos=cursorPosition();
  QString colorText=text();
  QStringList comp=colorText.split(" ");

  QRegExp rx(" ");
  int idx=0;
  int group=-1;

  while( (idx = rx.indexIn(colorText, idx)) != -1 ){
    group++;
    if(idx>=pos) break;
    idx+=rx.matchedLength();
  }
  if(idx==-1) group=comp.size()-1;

  if(group==-1) return;


  if(next){
    group++;
    if(group==comp.size()) group=0;
  }
  else{
    group--;
    if(group==-1) group=comp.size()-1;
  }

  int glen=comp[group].length();
  int gpos=0;
  for(int i=0; i<group; i++)
    gpos += comp[i].length();
  gpos+=group;

  setSelection(gpos, glen);
}

int ColorText::getGroup(){
  int pos=cursorPosition();
  QString colorText=text();
  QStringList comp=colorText.split(" ");

  QRegExp rx(" ");
  int idx=0;
  int group=-1;

  while( (idx = rx.indexIn(colorText, idx)) != -1 ){
    group++;
    if(idx>=pos) break;
    idx+=rx.matchedLength();
  }
  if(idx==-1) group=comp.size()-1;

  return group;
}

// --------------------------------------------- events ---------------------------------------------

void ColorText::keyPressEvent(QKeyEvent *e)
{
  QString keyText = e->text();
  int key=e->key();

  if(key==Qt::Key_Up){
    keyText="Up";
    increaseComponent();
  }
  else if(key==Qt::Key_Down){
    keyText="Down";
    decreaseComponent();
  }
  else{
    QLineEdit::keyPressEvent(e);
  }

}

bool ColorText::event(QEvent *e)
{
  if(e->type() == QEvent::KeyPress){
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);

    if ( ke->key() == Qt::Key_Tab ) {
      selectNextComponent();
      return true;
    }
    else if ( ke->key() == Qt::Key_Backtab ) {
      selectPrevComponent();
      return true;
    }

  }

  return QLineEdit::event(e);
}
