#include "colortext.h"

#include <QDebug>

#include "Service/validator.h"


ColorText::ColorText(QWidget *parent) : QLineEdit(parent)
{
  colorType = Vars::HSV;
  separator = " ";
}

void ColorText::setType(Vars::ColorType colorType) {
  this->colorType = colorType;
  if (colorType==Vars::Hex)
    separator = "";
}


void ColorText::updateText(QString text) {
  int pos = cursorPosition();
  setText(text);
  setCursorPosition(pos);
}



// --------------------------------------------- inc/dec component ---------------------------------------------

void ColorText::changeComponentVal(int pos, bool inc) {
  int val;
  int group = -1;
  bool ok;
  QStringList comp;
  QString valText, newValText;

  QString colorText = text();

  if (colorType==Vars::Hex) {
    if ( !Validator::checkValueHex(colorText) ) return;
    
    len = colorText.length();
    comp = getComponentsFromHex(colorText);
    group = getHexGroup(pos, len);
    
    val = comp[group].toInt(&ok, 16);
    
    if (inc) val++;
    else val--;
    if ( !Validator::checkComponentVal(val, colorType, group, len) ) return;
    
    comp[group] = QString("%1").arg( val, len/3, 16, QChar('0'));      
  }
  else {
    if ( !Validator::checkColorText(colorText, colorType) ) return;
    if ( !Validator::checkValueByType(colorText, colorType) ) return;
    
    comp = colorText.split(separator);
    QRegExp rx(" ");
    int idx = 0;

    while ( (idx = rx.indexIn(colorText, idx)) != -1 ) {
      group++;
      if (idx> = pos) break;
      idx+=rx.matchedLength();
    }
    if (idx==-1) group = comp.size()-1;
    if (group==-1) return;

    valText = comp[group];
    val = valText.toInt();

    if (inc) val++;
    else val--;
    if ( !Validator::checkComponentVal(val, colorType, group) ) return;

    newValText = QString::number(val);

    pos = (idx==-1) ? colorText.length() : idx;
    if (inc) {
      if ( newValText.length() > valText.length() ) pos++;
    }
    else {
      if ( newValText.length() < valText.length() ) pos--;
    }

    comp[group] = newValText;
  }

  colorText = comp.join(separator);
  setText(colorText);
  setCursorPosition(pos);

  textEdited(text());
}


// --------------------------------------------- select component ---------------------------------------------

void ColorText::selectNextComponent() {
  selectComponent(true);
}

void ColorText::selectPrevComponent() {
  selectComponent(false);
}

void ColorText::selectComponent(bool next) {
  int gpos = 0, glen;
  int group = -1;
  QStringList comp;

  int pos = cursorPosition();
  QString colorText = text();

  if (colorType==Vars::Hex) {
    if ( !Validator::checkValueHex(colorText) ) return;
    
    len = colorText.length();
    comp = getComponentsFromHex(colorText);
    group = getHexGroup(pos, len);
    group = getGroupNumber(group, comp.size(), next);
    
    glen = len/3;
    gpos = group*(len/3);
  }
  else {
    if ( !Validator::checkColorText(colorText, colorType) ) return;
    if ( !Validator::checkValueByType(colorText, colorType) ) return;
    
    comp = colorText.split(" ");
    QRegExp rx(" ");
    int idx = 0;

    while ( (idx = rx.indexIn(colorText, idx)) != -1 ) {
      group++;
      if (idx> = pos) break;
      idx+=rx.matchedLength();
    }
    if (idx==-1) group = comp.size()-1;
    if (group==-1) return;

    group = getGroupNumber(group, comp.size(), next);

    glen = comp[group].length();
    for (int i = 0; i<group; i++)
      gpos += comp[i].length();
    gpos+=group;
  }

  setSelection(gpos, glen);
}


// --------------------------------------------- service ---------------------------------------------

QStringList ColorText::getComponentsFromHex(QString hex) {
  QStringList list;

  int len = hex.length();
  int factor = len/3;

  for (int i = 0; i<3; i++)
    list.append( hex.mid(i*factor, factor) );

  return list;
}

int ColorText::getHexGroup(int pos, int len) {
  int group;

  if (len==3) {
    if ( pos==0 || pos==1 ) group = 0;
    if ( pos==2 ) group = 1;
    if ( pos==3 ) group = 2;
  }
  else if (len==6) {
    if ( pos==0 || pos==1 || pos==2 ) group = 0;
    if ( pos==3 || pos==4 ) group = 1;
    if ( pos==5 || pos==6 ) group = 2;
  }

  return group;
}

int ColorText::getGroupNumber(int group, int groupLen, bool next) {
  if (next) {
    group++;
    if (group==groupLen) group = 0;
  }
  else {
    group--;
    if (group==-1) group = groupLen-1;
  }

  return group;
}


// --------------------------------------------- events ---------------------------------------------

void ColorText::keyPressEvent(QKeyEvent *e)
{
  int key = e->key();
  
  int pos = cursorPosition();
  
  if (key == Qt::Key_Up) {
    changeComponentVal(pos, true);
  }
  else if (key == Qt::Key_Down) {
    changeComponentVal(pos, false);
  }
  else {
    QLineEdit::keyPressEvent(e);
  }
}

void ColorText::wheelEvent(QWheelEvent *e) {
  int delta = e->delta();
  int x = e->x();
  int y = e->y();
  
  int pos = cursorPositionAt(QPoint(x, y));
  
  
  changeComponentVal(pos, delta > 0);

  // qDebug() << QString("WHEEL: %1, [%2;%3], %4").arg(delta).arg(x).arg(y).arg(pos);
  
  e->accept();
}

bool ColorText::event(QEvent *e)
{
  if (e->type() == QEvent::KeyPress) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    
    if ( ke->key() == Qt::Key_Tab ) {
      if (ke->modifiers() == Qt::ControlModifier) {
        // nextInFocusChain()->setFocus(Qt::TabFocusReason);
        emit focusNextField();
        return true;
      }
      
      selectNextComponent();
      return true;
    }
    else if ( ke->key() == Qt::Key_Backtab ) {
      if (ke->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)) {
        // previousInFocusChain()->setFocus(Qt::BacktabFocusReason);
        emit focusPrevField();
        return true;
      }
      
      selectPrevComponent();
      return true;
    }

  }

  return QLineEdit::event(e);
}
