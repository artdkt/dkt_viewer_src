//
//  container.h
//  kickboxingplayer
//
//  Created by ogawa on 2015/05/25.
//
//

#include <stdio.h>
#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxGui.h"


class Container {

public:
  ofxIntSlider magnification;
  bool        zoomTest;     //-- bool zoom
  bool  	bFullscreen;     //-- fullscreen
  
  int hasOwnSoundFlag();
  int hasOwnZoomFlag();
  void allMoviePlay(bool _bool);
};