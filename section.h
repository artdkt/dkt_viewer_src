//
//  section.h
//  kickboxingplayer
//
//  Created by ogawa on 2015/05/25.
//
//
#include <stdio.h>
#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxGui.h"

class Section {
public:
  ofQTKitPlayer mov;
  ofPoint mov_pos, temp_mov_pos;
  ofPoint leftTop, rightBottom;
  ofxToggle soundToggle, zoomToggle;

  
  void setDivision(ofPoint _leftTop, ofPoint _rightBottom);

  /*--- constractor ---*/
  Section(string movName, ofPoint _leftTop, ofPoint _rightBottom) {
    mov.setPixelFormat(OF_PIXELS_RGBA);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    setDivision(_leftTop, _rightBottom);
  }
};
