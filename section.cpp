//
//  section.cpp
//  kickboxingplayer
//
//  Created by ogawa on 2015/05/25.
//
//

#include "section.h"

void Section::setDivision(ofPoint _leftTop, ofPoint _rightBottom) {
  leftTop = _leftTop;
  rightBottom = _rightBottom;
}

//void Section::emitEvent(bool &val){
//
//  ofNotifyEvent(onZoomChanged, sectionNumber); // CHECK: counld changes the statement of zoomToggle.
//
//}
//
//
//void Section::zoomChanged(int &num){
//  /* TODO: set flag of property Containers owns */
//  cout << num << endl;
//};
