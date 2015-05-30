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
  colorType=HSV;
  separator=" ";
}

void ColorText::setType(ColorText::ColorType colorType)
{
  this->colorType=colorType;
  if(colorType==Hex)
    separator="";
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

QStringList ColorText::getComponentsFromHex(QString hex){
  QStringList list;

  for(int i=0; i<3; i++)
    list.append( hex.mid(i*2, 2) );

  return list;
}

void ColorText::changeComponentVal(bool inc){
  int val;
  int group=-1;
  QString valText, newValText;
  QStringList comp;

  bool q=true;

  int pos=cursorPosition();
  QString colorText=text();

  if(colorType==Hex){
    comp=getComponentsFromHex(colorText);

    group=getHexGroup(pos);

//    if( pos==0 || pos==1 || pos==2 ) group=0;
//    if( pos==3 || pos==4 ) group=1;
//    if( pos==5 || pos==6 ) group=2;

    bool ok;
    val=comp[group].toInt(&ok, 16);

    if(!ok) return;

    if(inc) val++;                                                        // ---
    else val--;
    if( !checkVal(val, group) ) return;

    comp[group]=QString("%1").arg(val, 2, 16, QChar('0'));
  }
  else{
    comp=colorText.split(separator);


    QRegExp rx(" ");
    int idx=0;

    while( (idx = rx.indexIn(colorText, idx)) != -1 ){
      group++;
      if(idx>=pos) break;
      idx+=rx.matchedLength();
    }
    if(idx==-1) group=comp.size()-1;
    if(group==-1) return;


    valText=comp[group];
    val=valText.toInt();

//    if(q) return;

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
  }

  colorText=comp.join(separator);
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

int ColorText::getGroupNumber(int group, int len, bool next){
  if(next){
    group++;
    if(group==len) group=0;
  }
  else{
    group--;
    if(group==-1) group=len-1;
  }

  return group;
}

int ColorText::getHexGroup(int pos){
  int group;

  if( pos==0 || pos==1 || pos==2 ) group=0;
  if( pos==3 || pos==4 ) group=1;
  if( pos==5 || pos==6 ) group=2;

  return group;
}

void ColorText::selectComponent(bool next){
  int gpos=0, glen;
  int group=-1;
  QStringList comp;

  int pos=cursorPosition();
  QString colorText=text();

  if(colorType==Hex){
    comp=getComponentsFromHex(colorText);

    group=getHexGroup(pos);

//    if( pos==0 || pos==1 || pos==2 ) group=0;
//    if( pos==3 || pos==4 ) group=1;
//    if( pos==5 || pos==6 ) group=2;

    group=getGroupNumber(group, comp.size(), next);

//    if(next){
//      group++;
//      if(group==comp.size()) group=0;
//    }
//    else{
//      group--;
//      if(group==-1) group=comp.size()-1;
//    }

    glen=2;
    gpos=group*2;

//    setSelection(gpos, glen);
  }
  else{
    comp=colorText.split(" ");

    QRegExp rx(" ");
    int idx=0;

    while( (idx = rx.indexIn(colorText, idx)) != -1 ){
      group++;
      if(idx>=pos) break;
      idx+=rx.matchedLength();
    }
    if(idx==-1) group=comp.size()-1;

    if(group==-1) return;


//    if(next){
//      group++;
//      if(group==comp.size()) group=0;
//    }
//    else{
//      group--;
//      if(group==-1) group=comp.size()-1;
//    }

    group=getGroupNumber(group, comp.size(), next);

    glen=comp[group].length();
    for(int i=0; i<group; i++)
      gpos += comp[i].length();
    gpos+=group;

  }

  setSelection(gpos, glen);

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
