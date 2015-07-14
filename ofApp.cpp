#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  
    section_1 = new Section("movies/gpA.mov", ofPoint(0, 0), ofPoint(640, 360), 0);
    section_2 = new Section("movies/gpB.mov", ofPoint(640, 0), ofPoint(640, 360), 1);
    section_3 = new Section("movies/gpC.mov", ofPoint(0, 360), ofPoint(640, 360), 2);
    section_4 = new Section("movies/gpD.mov", ofPoint(640, 360), ofPoint(640, 360), 3);
  
    zoomFlags[0] = &section_1->zoomToggle;
    zoomFlags[1] = &section_2->zoomToggle;
    zoomFlags[2] = &section_3->zoomToggle;
    zoomFlags[3] = &section_4->zoomToggle;
  
    /*--- add something to click event ---*/
    section_1->zoomToggle.addListener(this, &ofApp::onZoomChanged_1);
    section_2->zoomToggle.addListener(this, &ofApp::onZoomChanged_2);

  
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
    gui.add(magnification.setup("magnification", 1, 1, 12));
  
    magnification = 1;
    bHide = false;
  
    // -- fullscreen
    
    bFullscreen = true;
    ofSetFullscreen(bFullscreen);
    ofShowCursor();
  
    temp = "---";
    singleClicked = false;
  
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
}


//--------------------------------------------------------------
void ofApp::draw() {
    ofSetHexColor(0xFFFFFF);
  
    // ---------
    maskFbo.begin();
    section_1->drawing(magnification, zoomOn, mov_pos);
    section_2->drawing(magnification, zoomOn, mov_pos);
    maskFbo.end();
    maskFbo.draw(ofGetWidth()/2-stageWidth/2,ofGetHeight()/2-stageHeight/2,stageWidth,stageHeight);
  
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
    ofRect(ofGetWidth()/2-stageWidth/2,ofGetHeight()/2-stageHeight/2,stageWidth,stageHeight);
    ofSetLineWidth(0.5);
    ofLine(ofGetWidth()/2, ofGetHeight()/2 - stageHeight/2, ofGetWidth()/2, ofGetHeight()/2 + stageHeight/2);
    ofLine(ofGetWidth()/2 -stageWidth/2, ofGetHeight()/2, ofGetWidth()/2 + stageWidth/2, ofGetHeight()/2);
    
    //--------------------------
    //---- SeekBar
    
    ofPushMatrix();
    
    ofFill();
    ofTranslate(ofGetWidth()/2 -stageWidth/2, ofGetHeight()/2 + stageHeight/2 +40);
    
    ofSetHexColor(0x111111);
    ofRect(0, 0, stageWidth, 20);
    ofSetHexColor(0xFF0000);
    ofRect(0, 0, stageWidth * ((float)section_1->mov.getCurrentFrame() / (float)section_1->mov.getTotalNumFrames()), 20);
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString(timecode, stageWidth * ((float)section_1->mov.getCurrentFrame() / (float)section_1->mov.getTotalNumFrames()), 40);
    
    ofPopMatrix();
  
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
    } else {
        section_1->mov.play();
        section_2->mov.play();
    }
  
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
        if (y > ofGetHeight()/2 + stageHeight/2 +40 && y < ofGetHeight()/2 + stageHeight/2 +40 +20) {
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
    
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
        if (y > ofGetHeight()/2 + stageHeight/2 +40 && y < ofGetHeight()/2 + stageHeight/2 +40 +20) {
            
            if(seek){
                float x_pos = x - (ofGetWidth()/2-stageWidth/2);
                float hoge  = x_pos / stageWidth;
                section_1->mov.setPosition(hoge);
            }
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
  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  
    // supporting zoom to double click
    if(zoomOn && checkingdoubleClicked()) {
      cout << "x=" << x << ", y=" <<  y << endl;
      magnification =  magnification + 1;
      section_1->mov.draw(x, y, 1280*magnification, 720*magnification); // kokoga umaku ittenai
    }
  
  
    // seek
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
      if (y > ofGetHeight()/2 + stageHeight/2 +40 && y < ofGetHeight()/2 + stageHeight/2 +40 +20) {
        play = false;
        seek = true;
        float x_pos = x - (ofGetWidth()/2-stageWidth/2);
        float hoge  = x_pos / stageWidth;
        section_1->mov.setPosition(hoge);
      }
    }
    
    // --- drag
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
        if (y > ofGetHeight()/2 - stageHeight/2 && ofGetHeight()/2 + stageHeight/2) {
            if (zoomOn && !dragMov) {
                // set begin point
                
                beginDrag.x = x;
                beginDrag.y = y;
                dragMov = true;
            }
        }
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

void ofApp::manipulateZooms(int sectionNum) {
  forceFalsedZoomFlags(sectionNum);
  checkingZoomOn();
}

void ofApp::forceFalsedZoomFlags(int sectionNum) {
  for (int i = 0; i < 4; i ++) {  // TODO: kill magic number.
    if (i != sectionNum) {
//      cout << *zoomFlags[i] << endl;
      *zoomFlags[i] = false;
    }
  }
};

void ofApp::checkingZoomOn() {
  cout << "aaa" << endl;
  for (int i = 0; i < 4; i ++) {  // TODO: kill magic number.
    if (*zoomFlags[i]) {
      zoomOn = true;
      return 0;
    }
  }
  zoomOn = false;
}

/* ---------------- events function --------------------*/
void ofApp::onZoomChanged_1(bool &state) {
  
  manipulateZooms(section_1->sectionNumber);
  /* TODO: set flag of property Containers owns */
};

void ofApp::onZoomChanged_2(bool &state) {
  
  manipulateZooms(section_2->sectionNumber);
  /* TODO: set flag of property Containers owns */
};







