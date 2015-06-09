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

void Section::drawing(int magnitude, bool zoomOn, ofPoint mov_pos){
  // pattern: any displayings normally sets
  if (!zoomToggle && !zoomOn) {
    mov.draw(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);
  }
  
  if (zoomToggle) {
    cout << mov_pos.x << endl;
    mov.draw(mov_pos.x, mov_pos.y, 1280 * magnitude, 720 * magnitude);
  }
}

