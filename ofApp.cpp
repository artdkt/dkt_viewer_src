#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  
  section_1 = new Section("movies/gpA.mov", ofPoint(0, 0), ofPoint(640, 360), 0);
  section_2 = new Section("movies/gpB.mov", ofPoint(640, 0), ofPoint(640, 360), 1);
  section_3 = new Section("movies/gpC.mov", ofPoint(0, 360), ofPoint(640, 360), 2);
  section_4 = new Section("movies/gpD.mov", ofPoint(640, 360), ofPoint(640, 360), 3);
  
  
  sections[0] = section_1;
  sections[1] = section_2;
  sections[2] = section_3;
  sections[3] = section_4;
  
  /*--- add something to click event ---*/
  section_1->zoomToggle.addListener(this, &ofApp::onZoomChanged_1);
  section_2->zoomToggle.addListener(this, &ofApp::onZoomChanged_2);
  section_3->zoomToggle.addListener(this, &ofApp::onZoomChanged_3);
  section_4->zoomToggle.addListener(this, &ofApp::onZoomChanged_4);
  
  
  ofBackground(20, 20, 20);
  zoomOn = false;
  
  
  //--------------------------
  //-- drag
  //
  
  beginDrag, transfer, mov_pos, temp_mov_pos = ofPoint(0, 0);
  dragMov = false;
  
  
  //ofEnableAlphaBlending();
  
  stageWidth  = 1280;
  stageHeight = 720;
  
  //--------------------------
  // ---- movie setting
  //
  
  maskFbo.allocate(stageWidth, stageHeight);
  frameByframe = false;
  
  allMoviePlay(true);
  
  maskFbo.begin();
  ofClear(0, 0, 0, 255);
  maskFbo.end();
  
  //--------------------------
  //-- gui
  
  gui.setup();
  gui.add(play.setup("play", true));
  gui.add(zoomLabel.setup("zoom", ""));
  gui.add(section_1->zoomToggle.setup("section_1", false));
  gui.add(section_2->zoomToggle.setup("section_2", false));
  gui.add(section_3->zoomToggle.setup("section_3", false));
  gui.add(section_4->zoomToggle.setup("section_4", false));
  gui.add(magnification.setup("magnification", 1, 1, 12));
  
  magnification = 1;
  bHide = false;
  
  // -- fullscreen
  
  bFullscreen = true;
  ofSetFullscreen(bFullscreen);
  ofShowCursor();
  
  temp = "---";
  singleClicked = false;
  
  area_top.set(ofGetWidth()/2-stageWidth/2, ofGetHeight()/2-stageHeight/2);
  area_bottom.set(ofGetWidth()/2 + stageWidth/2, ofGetHeight()/2 + stageHeight/2);
}

//--------------------------------------------------------------
void ofApp::update() {
  
  ofShowCursor();
  
  section_1->mov.update();
  section_2->mov.update();
  
  //--------------------------
  //---- outputString
  
  float   f = (section_1->mov.getPosition() * section_1->mov.getDuration()) - (int)(section_1->mov.getPosition() * section_1->mov.getDuration());
  int frame = f * (float)section_1->mov.getTotalNumFrames() / section_1->mov.getDuration();
  int     s = section_1->mov.getPosition() * section_1->mov.getDuration();
  s = s % 60;
  int     m = s / 60;
  m = m % 60;
  int     h = m / 60;
  
  timecode = ofToString(h) + ":" + ofToString(m) + ":" + ofToString(s) + ":" + ofToString(frame);
  
  str =   "TimeCode: " + timecode + "\n";
  str +=  "frame: " + ofToString(section_1->mov.getCurrentFrame()) + "/" + ofToString(section_1->mov.getTotalNumFrames()) + "\n";
  str +=  "duration: " + ofToString(section_1->mov.getPosition() * section_1->mov.getDuration(), 2) + "/" + ofToString(section_1->mov.getDuration(), 2) + "\n";
  str +=  "movfps: " + ofToString((float)section_1->mov.getTotalNumFrames() / section_1->mov.getDuration(), 2)+ "\n";
  str +=  "macfps"    + ofToString(ofGetFrameRate(), 2)+"fps" + "\n";
  str +=  "mov_pos_x: "    + ofToString(mov_pos.x)+ "  mov_pos_y: " + ofToString(mov_pos.y)+ "\n";
  str +=  "temp" + temp +  "\n";
  
  //--------------------------
  //--- soundControl
  
  //    if (movie00) {
  //        mov00.setVolume(1.0);
  //    } else {
  //        mov00.setVolume(0.0);
  //    }
  //
  //    if (movie01) {
  //        mov01.setVolume(1.0);
  //    } else {
  //        mov01.setVolume(0.0);
  //    }
  //
  //    if (movie02) {
  //        mov02.setVolume(1.0);
  //    } else {
  //        mov02.setVolume(0.0);
  //    }
  //
  //    if (movie03) {
  //        mov03.setVolume(1.0);
  //    } else {
  //        mov03.setVolume(0.0);
  //    }
  
  //--------------------------
  
  updateLoopState(loop_in_point, loop_out_point);


}


//--------------------------------------------------------------
void ofApp::draw() {
  ofSetHexColor(0xFFFFFF);

  
  // ---------
  maskFbo.begin();
  section_1->drawing(magnification, zoomOn, mov_pos);
  section_2->drawing(magnification, zoomOn, mov_pos);
  section_3->drawing(magnification, zoomOn, mov_pos);
  section_4->drawing(magnification, zoomOn, mov_pos);
  maskFbo.end();
  maskFbo.draw(area_top.x, area_top.y, stageWidth, stageHeight);
  
  //--------------------------
  //---- information
  
  ofSetHexColor(0xFFFFFF);
  ofDrawBitmapString(str, 10, 20);
  ofDrawBitmapString(eventString, 20,80);
  
  allMoviePlay(play);
  
  //--------------------------
  //-- GUI
  
  if( bHide ){
    gui.draw();
  }
  
  //--------------------------
  //--- stageFrame
  
  ofNoFill();
  ofSetLineWidth(1.0);
  ofRect(area_top.x, area_top.y, stageWidth, stageHeight);
  ofSetLineWidth(0.5);
  ofLine(ofGetWidth()/2, area_top.y, ofGetWidth()/2, area_bottom.y);
  ofLine(area_top.x, ofGetHeight()/2, area_bottom.x, ofGetHeight()/2);
  
  //--------------------------
  //---- SeekBar
  
  ofPushMatrix();
  ofFill();
  ofTranslate(area_top.x, area_bottom.y + 10); //ここがseekバーの位置
  
  ofSetHexColor(0x111111);
  ofRect(0, 0, stageWidth, 20);
  ofSetHexColor(0xFF0000);
  ofRect(0, 0, stageWidth * ((float)section_1->mov.getCurrentFrame() / (float)section_1->mov.getTotalNumFrames()), 20);
  ofSetHexColor(0xFFFFFF);
  ofDrawBitmapString(timecode, stageWidth * ((float)section_1->mov.getCurrentFrame() / (float)section_1->mov.getTotalNumFrames()), 40);
  
  ofPopMatrix();
  
  //--------------------------
  //---- loop bar
  ofSetHexColor(0xAAAAAA);
  ofRect(area_top.x, area_bottom.y + 2, area_bottom.x - area_top.x, 5);
  ofSetHexColor(0x0000FF);
  ofRect(loop_in_point, area_bottom.y + 2, loop_out_point -loop_in_point, 5);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  
  if( key == 'h' ){
    bHide = !bHide;
  }
  
  if(key == ' ') {
    play = !play;
  }
  
  if(key == 'f') {
    bFullscreen = !bFullscreen;
    ofSetFullscreen(bFullscreen);
  }
  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  
}

//--------------------------------------------------------------
void ofApp::allMoviePlay(bool _bool){
  
  if (!_bool) {
    section_1->mov.stop();
    section_2->mov.stop();
    section_3->mov.stop();
    section_4->mov.stop();
  } else {
    section_1->mov.play();
    section_2->mov.play();
    section_3->mov.play();
    section_4->mov.play();

  }
  
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  
  if (x > area_top.x && x < area_bottom.x) {
    if (y > area_bottom.y + 10 && y < area_bottom.y + 10 +20) {
      ofBackground(0, 0, 0);
    } else {
      ofBackground(20, 20, 20);
    }
  } else {
    ofBackground(20, 20, 20);
  }
  
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  
  //--------------------------
  // seek
  
  if(seekBarAreaIs(x, y)) {
    if(seek){
      float x_pos = x - (ofGetWidth()/2-stageWidth/2);
      float hoge  = x_pos / stageWidth;
      section_1->mov.setPosition(hoge);
      section_2->mov.setPosition(hoge);
      section_3->mov.setPosition(hoge);
      section_4->mov.setPosition(hoge);

    }
  }
  
  
  //--------------------------
  //-- zoom drag
  
  if (dragMov) {
    
    transfer.x = x - beginDrag.x;
    transfer.y = y - beginDrag.y;
    
    transfer += temp_mov_pos;
    
    //------ zoom
    mov_pos = transfer;
    
  }
  
  // loop bar
  if (loopBarAreaIs(x, y)) {
    loopbar_dragging = true;
    loop_out_point = x;
  }
  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  
  // supporting zoom to double click
  if(zoomOn && checkingdoubleClicked()) {
    magnification =  magnification + 1;
    if(current_zoom_num > 0) {
      sections[current_zoom_num]->mov.draw(x, y, 1280*magnification, 720*magnification);
    }
  }
  
  // seek
  if (seekBarAreaIs(x, y)) {
    play = false;
    seek = true;
    float x_pos = x - area_top.x;
    float hoge  = x_pos / stageWidth;
    section_1->mov.setPosition(hoge); // 妥協
  }
  
  // --- drag zoom系だこれ
  if (x > area_top.x && x < area_bottom.x) {
    if (y > area_top.y && area_bottom.y) {
      if (zoomOn && !dragMov) {
        // set begin point
        
        beginDrag.x = x;
        beginDrag.y = y;
        dragMov = true;
      }
    }
  }
  
  // loop bar
  if (loopBarAreaIs(x, y)) {
    loopbar_dragging = false;
    loop_in_point = x;
    loop_out_point = x;
  }
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  //-- seek
  if(seek){
    play = true;
    seek = !seek;
  }
  
  //-- drag
  if(dragMov){
    temp_mov_pos = mov_pos;
    dragMov = !dragMov;
  }
  
  // loop bar
  if(!loopbar_dragging) {
    loop_in_point = 0;
    loop_out_point = 0;
  }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
  
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
  
}


/* ---------------- asset function --------------------*/

void ofApp::updateCurrentFrame() {
  for (int i = 0; i < 4; i++) {
    if (sections[i]->mov.isPlaying()) {
      current_frame = sections[i]->mov.getCurrentFrame();
      return;
    }
  }
}

bool ofApp::seekBarAreaIs(int x, int y) {
  if (x > area_top.x && x < area_bottom.x) {
    if (y > area_bottom.y +10 && y < area_bottom.y +10 +20) {
      return true;
    }
  }
  return false;
}

bool ofApp::loopBarAreaIs(int x, int y) {
  if (x > area_top.x && x < area_bottom.x) {
    if (y > area_bottom.y +2 && y < area_bottom.y + 2 + 5) {  // offsetゼロで矩形サイズは5で設定
      return true;
    }
  }
  return false;
}

void ofApp::updateLoopState(int in_point, int out_point) {
  switch (loop) {
    case 0:
      if (loop_in_point != 0 && loop_out_point != 0) {
        section_1->mov.setPosition( (in_point - area_top.x) / stageWidth);
        section_2->mov.setPosition( (in_point - area_top.x) / stageWidth);
        section_3->mov.setPosition( (in_point - area_top.x) / stageWidth);
        section_4->mov.setPosition( (in_point - area_top.x) / stageWidth);
        loop = 1;
      }
      return;
    case 1:
      if (loop_in_point != 0 && loop_out_point != 0) {
        if ( section_1->mov.getPosition() * stageWidth + area_top.x > out_point) {
          section_1->mov.setPosition( (in_point - area_top.x) / stageWidth);
          section_2->mov.setPosition( (in_point - area_top.x) / stageWidth);
          section_3->mov.setPosition( (in_point - area_top.x) / stageWidth);
          section_4->mov.setPosition( (in_point - area_top.x) / stageWidth);
          
        }
      return;
      }

  }
  loop = 0;
}

bool ofApp::checkingdoubleClicked() {
  if (singleClicked == false) {
    startTime = clock();
    singleClicked = true;
    return false;
  } else {
    endTime = clock();
    double diffTIme = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000;
    if (diffTIme < 1000) { // put detection time to double click.
      singleClicked = false;
      return true;
    } else {
      startTime = clock();
      return false;
    }
  }
}

void ofApp::manipulateZooms(int sectionNum, bool &state) {
  checkingZoomOn();
  if (zoomOn && !state) {
    return 0;
    
  }
  forceFalsedZoomFlags(sectionNum);
}

void ofApp::forceFalsedZoomFlags(int sectionNum) {
  for (int i = 0; i < 4; i ++) {  // TODO: kill magic number.
    if (i != sectionNum) {
      sections[i]->zoomToggle = false;
    }
  }
};

void ofApp::checkingZoomOn() {
  for (int i = 0; i < 4; i ++) {  // TODO: kill magic number.
    if (sections[i]->zoomToggle) {
      zoomOn = true;
      current_zoom_num = i;
      return 0;
    } else {
      current_zoom_num = -1;
    }
  }
  
  zoomOn = false;
}

/* ---------------- events function --------------------*/
void ofApp::onZoomChanged_1(bool &state) {
  manipulateZooms(section_1->sectionNumber, state);
};

void ofApp::onZoomChanged_2(bool &state) {
  manipulateZooms(section_2->sectionNumber, state);
};

void ofApp::onZoomChanged_3(bool &state) {
  manipulateZooms(section_3->sectionNumber, state);
};

void ofApp::onZoomChanged_4(bool &state) {
  manipulateZooms(section_4->sectionNumber, state);
};




