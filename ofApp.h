#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxGui.h"
#include "section.h"

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
    
    ofPoint beginDrag;      //
    ofPoint transfer;       //
    ofPoint mov_pos;        //
    ofPoint temp_mov_pos;   //
    
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

    clock_t startTime, endTime;
    bool singleClicked;
    bool checkingdoubleClicked();
  
    //-- string
    string str;
    string timecode;
    string temp;
  
    /*--- testing section class ---*/
    Section *my_section1;
    void listenToggle(ofxToggle &val);
  
};






