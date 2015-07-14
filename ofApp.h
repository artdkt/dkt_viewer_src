#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxGui.h"
#include "section.h"

#define ELEM(array) (sizeof (array) / sizeof *(array))



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

    bool frameByframe;
    ofFbo maskFbo;
    
    int stageWidth;
    int stageHeight;
    
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
    ofxLabel    zoomLabel;

    ofxIntSlider magnification;
    ofxFloatSlider pos_x;
    ofxFloatSlider pos_y;
  
    ofxPanel gui;
  
    bool        zoomOn;     //-- bool zoom
    bool  	bFullscreen;     //-- fullscreen

    clock_t startTime, endTime;
    bool singleClicked;
    bool checkingdoubleClicked();
  
    //-- string
    string str;
    string timecode;
    string temp;
  
    /*--- testing section class ---*/
    Section *section_1, *section_2, *section_3, *section_4;
    void onZoomChanged_1(bool &state), onZoomChanged_2(bool &state);

    void manipulateZooms(int sectionNum);
    void forceFalsedZoomFlags(int sectionNum);
    void checkingZoomOn();
  
    /*--- testing component variables ---*/
    ofxToggle *zoomFlags[4];
  
};






