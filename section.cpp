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

void Section::drawing(int magnitude, bool zoomOn){

  if (!zoomToggle || !zoomOn) {
    return 0;
  }
  if (zoomToggle) {
    mov.draw(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);
  }
}




/*deplecated*/

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
