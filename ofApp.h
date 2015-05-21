#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void allMoviePlay(bool _bool);
    
    
    ofQTKitPlayer   mov00;
    ofQTKitPlayer   mov01;
    ofQTKitPlayer   mov02;
    ofQTKitPlayer   mov03;
    
    bool            frameByframe;
    
    ofFbo           maskFbo;
    
    int             stageWidth;
    int             stageHeight;
    
    //----event
    
    char eventString[255];
    bool seek;
    
    //----drag
    
    bool dragMov;
    
    ofPoint beginDrag;      // ドラッグを始めた最初の位置
    ofPoint transfer;       // 変化量
    ofPoint mov_pos;        // 映像の位置
    ofPoint temp_mov_pos;   // 映像の座標を一時的に保管
    
    //----gui
    
    bool bHide;
    
    ofxToggle   play;
    
    ofxLabel    soundLabel;
    ofxToggle   movie00;
    ofxToggle   movie01;
    ofxToggle   movie02;
    ofxToggle   movie03;
    
    ofxLabel    zoomLabel;
    ofxToggle   zoom00;
    ofxToggle   zoom01;
    ofxToggle   zoom02;
    ofxToggle   zoom03;
    
    ofxIntSlider magnification;
    ofxFloatSlider pos_x;
    ofxFloatSlider pos_y;
  
    ofxPanel gui;
  
    bool        zoomTest;     //-- bool zoom
    bool  	bFullscreen;     //-- fullscreen
    
    //-- string
    string str;
    string timecode;
    string temp;
    
};
