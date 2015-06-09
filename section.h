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
  ofPoint leftTop, rightBottom;
  ofxToggle zoomToggle;
  int sectionNumber;

  void setDivision(ofPoint _leftTop, ofPoint _rightBottom);
  void drawing(int magnitude, bool zoomOn, ofPoint mov_pos);
  


  /*--- constractor ---*/
  Section(string movName, ofPoint _leftTop, ofPoint _rightBottom, int _sectionNumber) {
    mov.setPixelFormat(OF_PIXELS_RGBA);
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    sectionNumber = _sectionNumber;
    setDivision(_leftTop, _rightBottom);
    mov.loadMovie(movName, decodeMode);
  }
  
};
