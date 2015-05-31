#include "colortext.h"

#include <QDebug>

#include "validator.h"

// -------------------------------------------- consts --------------------------------------------

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
const int minSHex=0;
const int maxSHex=15;


// ----------------------------------------------------------------------------------------------------

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


// bool ColorText::checkVal(int val, int group, int hexLen, int colorType){
//   if(colorType==HSV){
//     switch(group){
//     case 0:
//       return (val>=minH && val<=maxH);
//       break;
//     case 1:
//       return (val>=minS && val<=maxS);
//       break;
//     case 2:
//       return (val>=minV && val<=maxV);
//       break;
//     }
//   }

//   if(colorType==RGB){
//     return (val>=minRGB && val<=maxRGB);
//   }

//   if(colorType==CMYK){
//     switch(group){
//     case 0:
//       return (val>=minC && val<=maxC);
//       break;
//     case 1:
//       return (val>=minM && val<=maxM);
//       break;
//     case 2:
//       return (val>=minY && val<=maxY);
//       break;
//     case 3:
//       return (val>=minK && val<=maxK);
//       break;
//     }
//   }

//   if(colorType==Hex){
//     if(hexLen==3)
//       return (val>=minSHex && val<=maxSHex);
//     else if(hexLen==6)
//       return (val>=minHex && val<=maxHex);
//   }
// }

// --------------------------------------------- inc/dec component ---------------------------------------------

void ColorText::increaseComponent(){
  changeComponentVal(true);
}

void ColorText::decreaseComponent(){
  changeComponentVal(false);
}

void ColorText::changeComponentVal(bool inc){
  int val;
  int group=-1;
  bool ok;
  QStringList comp;
  QString valText, newValText;

  int pos=cursorPosition();
  QString colorText=text();

  if(colorType==Hex){
    if( !Validator::checkValueHex(colorText) ) return;
    
    len=colorText.length();
    comp=getComponentsFromHex(colorText);
    group=getHexGroup(pos, len);
    
    val=comp[group].toInt(&ok, 16);
    
    if(inc) val++;                                                        // ---
    else val--;
    if( !Validator::checkComponentVal(val, colorType, group, len) ) return;
    
    comp[group]=QString("%1").arg( val, len/3, 16, QChar('0'));      
  }
  else{
    if( !Validator::checkColorText(colorText, colorType) ) return;
    if( !Validator::checkValueByType(colorText, colorType) ) return;
    
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

    if(inc) val++;                                                        // ---
    else val--;
    if( !Validator::checkComponentVal(val, colorType, group) ) return;

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

void ColorText::selectComponent(bool next){
  int gpos=0, glen;
  int group=-1;
  QStringList comp;

  int pos=cursorPosition();
  QString colorText=text();

  if(colorType==Hex){
    if( !Validator::checkValueHex(colorText) ) return;
    
    len=colorText.length();
    comp=getComponentsFromHex(colorText);
    group=getHexGroup(pos, len);
    group=getGroupNumber(group, comp.size(), next);
    
    glen=len/3;
    gpos=group*(len/3);
  }
  else{
    if( !Validator::checkColorText(colorText, colorType) ) return;
    if( !Validator::checkValueByType(colorText, colorType) ) return;
    
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

// --------------------------------------------- service ---------------------------------------------

QStringList ColorText::getComponentsFromHex(QString hex){
  QStringList list;

  int len=hex.length();
  int factor=len/3;

  for(int i=0; i<3; i++)
    list.append( hex.mid(i*factor, factor) );

  return list;
}

int ColorText::getHexGroup(int pos, int len){
  int group;

  if(len==3){
    if( pos==0 || pos==1 ) group=0;
    if( pos==2 ) group=1;
    if( pos==3 ) group=2;
  }
  else if(len==6){
    if( pos==0 || pos==1 || pos==2 ) group=0;
    if( pos==3 || pos==4 ) group=1;
    if( pos==5 || pos==6 ) group=2;
  }

  return group;
}

int ColorText::getGroupNumber(int group, int groupLen, bool next){
  if(next){
    group++;
    if(group==groupLen) group=0;
  }
  else{
    group--;
    if(group==-1) group=groupLen-1;
  }

  return group;
}

// bool ColorText::checkValueHex(QString text){    // +++ duplicate ColorProcessor
//   int len=text.length();
//   if( len!=6 && len!=3 ) return false;
  
//   bool ok;
//   int factor=len/3;

//   for(int i=0; i<3; i++){
//     QString comp = text.mid(i*factor, factor);
//     int val=comp.toInt(&ok, 16);
//     if(!ok) return false;

//     if(len==3)
//       if(val<minSHex || val>maxSHex) return false;
//     else
//       if(val<minHex || val>maxHex) return false;
//   }

//   return true;
// }
