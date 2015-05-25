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
  ofPoint mov_pos;
  ofPoint temp_mov_pos;
  ofxToggle   soundToggle;
  ofxToggle   zoomToggle;
};
