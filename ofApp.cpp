#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(20, 20, 20);
    zoomTest = false;
    
    //--------------------------
    //-- drag
    //
    
    beginDrag, transfer, mov_pos, temp_mov_pos = ofPoint(0, 0);
    dragMov = false;
    
    //ofEnableAlphaBlending();
    
    stageWidth  = 1280;
    stageHeight = 720;
    
    //--------------------------
    // ---- setting for movie
    
    maskFbo.allocate(stageWidth, stageHeight);
    
    frameByframe = false;
    
    mov00.setPixelFormat(OF_PIXELS_RGBA);
    mov01.setPixelFormat(OF_PIXELS_RGBA);
    mov02.setPixelFormat(OF_PIXELS_RGBA);
    mov03.setPixelFormat(OF_PIXELS_RGBA);
    
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    mov00.loadMovie("movies/gpA.mov", decodeMode);
    mov01.loadMovie("movies/gpB.mov", decodeMode);
    mov02.loadMovie("movies/gpC.mov", decodeMode);
    mov03.loadMovie("movies/gpD.mov", decodeMode);
    
    allMoviePlay(true);
    
    maskFbo.begin();
    ofClear(0, 0, 0, 255);
    maskFbo.end();
    
    //--------------------------
    //-- gui
    
    gui.setup();
    gui.add(play.setup("play", true));
    
    gui.add(soundLabel.setup("sound", ""));
    gui.add(movie00.setup("movie00", true));
    gui.add(movie01.setup("movie01", false));
    gui.add(movie02.setup("movie02", false));
    gui.add(movie03.setup("movie03", false));
    
    gui.add(zoomLabel.setup("zoom", ""));
    gui.add(zoom00.setup("zoom00", false));
    gui.add(zoom01.setup("zoom01", false));
    gui.add(zoom02.setup("zoom02", false));
    gui.add(zoom03.setup("zoom03", false));
  
    gui.add(magnification.setup("magnification", 1, 1, 12));
    
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
    
    mov00.update();
    mov01.update();
    mov02.update();
    mov03.update();
  
    //--------------------------
    //---- outputString
    
    float   f = (mov00.getPosition() * mov00.getDuration()) - (int)(mov00.getPosition() * mov00.getDuration());
    int frame = f * (float)mov00.getTotalNumFrames() / mov00.getDuration();
    int     s = mov00.getPosition() * mov00.getDuration();
    s = s % 60;
    int     m = s / 60;
    m = m % 60;
    int     h = m / 60;
    
    timecode = ofToString(h) + ":" + ofToString(m) + ":" + ofToString(s) + ":" + ofToString(frame);
    
    str =   "TimeCode: " + timecode + "\n";
    str +=  "frame: " + ofToString(mov00.getCurrentFrame()) + "/" + ofToString(mov00.getTotalNumFrames()) + "\n";
    str +=  "duration: " + ofToString(mov00.getPosition() * mov00.getDuration(), 2) + "/" + ofToString(mov00.getDuration(), 2) + "\n";
    str +=  "movfps: " + ofToString((float)mov00.getTotalNumFrames() / mov00.getDuration(), 2)+ "\n";
    str +=  "macfps"    + ofToString(ofGetFrameRate(), 2)+"fps" + "\n";
    str +=  "mov_pos_x: "    + ofToString(mov_pos.x)+ "  mov_pos_y: " + ofToString(mov_pos.y)+ "\n";
    str +=  "temp" + temp +  "\n";
  
    //--------------------------
    //--- soundControl
    
    if (movie00) {
        mov00.setVolume(1.0);
    } else {
        mov00.setVolume(0.0);
    }
    
    if (movie01) {
        mov01.setVolume(1.0);
    } else {
        mov01.setVolume(0.0);
    }
    
    if (movie02) {
        mov02.setVolume(1.0);
    } else {
        mov02.setVolume(0.0);
    }
    
    if (movie03) {
        mov03.setVolume(1.0);
    } else {
        mov03.setVolume(0.0);
    }
    
    //--------------------------

  
    if(zoom00) {
        zoom01 = false;
        zoom02 = false;
        zoom03 = false;
    } else if(zoom01) {
        zoom00 = false;
        zoom02 = false;
        zoom03 = false;
    } else if(zoom02) {
        zoom00 = false;
        zoom01 = false;
        zoom03 = false;
    } else if(zoom03) {
        zoom00 = false;
        zoom01 = false;
        zoom02 = false;
    }
    if(zoom00 || zoom01 || zoom02 || zoom03) {
        zoomTest = true;
    } else {
        zoomTest = false;
        magnification = 1;
    }
  
}


//--------------------------------------------------------------
void ofApp::draw() {
  
    ofSetHexColor(0xFFFFFF);
  
    // ---------
    
    if(zoom00){
        maskFbo.begin();
        mov00.draw(0, 0, 640, 360);
        mov01.draw(640,0, 640, 360);
        mov02.draw(0, 360, 640, 360);
        mov03.draw(640, 360, 640, 360);
        ofClear(0, 0, 0, 255);
        mov00.draw(mov_pos.x, mov_pos.y, 1280*magnification, 720*magnification);
        maskFbo.end();
    } else if(zoom01) {
        maskFbo.begin();
        mov00.draw(0, 0, 640, 360);
        mov02.draw(0, 360, 640, 360);
        mov03.draw(640, 360, 640, 360);
        ofClear(0, 0, 0, 255);
        mov01.draw(mov_pos.x, mov_pos.y, 1280*magnification, 720*magnification);
        maskFbo.end();
    } else if(zoom02) {
        maskFbo.begin();
        mov00.draw(0, 0, 640, 360);
        mov01.draw(640,0, 640, 360);
        mov03.draw(640, 360, 640, 360);
        ofClear(0, 0, 0, 255);
        mov02.draw(mov_pos.x, mov_pos.y, 1280*magnification, 720*magnification);
        maskFbo.end();
    } else if(zoom03) {
        maskFbo.begin();
        mov00.draw(0, 0, 640, 360);
        mov01.draw(640,0, 640, 360);
        mov02.draw(0, 360, 640, 360);
        ofClear(0, 0, 0, 255);
        mov03.draw(mov_pos.x, mov_pos.y, 1280*magnification, 720*magnification);
        maskFbo.end();
    } else {
        mov_pos = ofPoint(0, 0);
        temp_mov_pos = ofPoint(0, 0);
        
        maskFbo.begin();
        mov00.draw(0, 0, 640, 360);
        mov01.draw(640,0, 640, 360);
        mov02.draw(0, 360, 640, 360);
        mov03.draw(640, 360, 640, 360);
        maskFbo.end();
    }

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
    ofRect(0, 0, stageWidth * ((float)mov00.getCurrentFrame() / (float)mov00.getTotalNumFrames()), 20);
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString(timecode, stageWidth * ((float)mov00.getCurrentFrame() / (float)mov00.getTotalNumFrames()), 40);
    
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
        mov00.stop();
        mov01.stop();
        mov02.stop();
        mov03.stop();
    } else {
        mov00.play();
        mov01.play();
        mov02.play();
        mov03.play();
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
                mov00.setPosition(hoge);
                mov01.setPosition(hoge);
                mov02.setPosition(hoge);
                mov03.setPosition(hoge);
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
    if(zoomTest && checkingdoubleClicked()) {
      cout << "x=" << x << ", y=" <<  y << endl;
      magnification =  magnification + 1;
      mov01.draw(x, y, 1280*magnification, 720*magnification); // kokoga umaku ittenai
    }
  
  
    // seek
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
      if (y > ofGetHeight()/2 + stageHeight/2 +40 && y < ofGetHeight()/2 + stageHeight/2 +40 +20) {
        play = false;
        seek = true;
        float x_pos = x - (ofGetWidth()/2-stageWidth/2);
        float hoge  = x_pos / stageWidth;
        mov00.setPosition(hoge);
        mov01.setPosition(hoge);
        mov02.setPosition(hoge);
        mov03.setPosition(hoge);
        
      }
    }
    
    // --- drag
    if (x > ofGetWidth()/2 - stageWidth/2 && x < ofGetWidth()/2 + stageWidth/2) {
        if (y > ofGetHeight()/2 - stageHeight/2 && ofGetHeight()/2 + stageHeight/2) {
            
            if (zoomTest && !dragMov) {
                
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




