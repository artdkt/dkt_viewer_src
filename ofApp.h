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
  

    bool frameByframe;
    ofFbo maskFbo;
    
    int stageWidth;
    int stageHeight;
    ofPoint area_top;
    ofPoint area_bottom;
    int current_frame;  // grobal storing frame;
  
    void allMoviePlay(bool _bool);
    void updateCurrentFrame();
  
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
  
    /*--- loopbar variable and functions ---*/
    int loop_in_point;
    int loop_out_point;
    bool loopbar_dragging;
    int loop;  // 0 = false and first set, 1 = looping state.
    bool loopBarAreaIs(int x, int y);
    void updateLoopState(int in_point, int out_poinr);
  
  
    /*--- section class ---*/
    Section *section_1, *section_2, *section_3, *section_4;
    Section *sections[4];
    void onZoomChanged_1(bool &state), onZoomChanged_2(bool &state), onZoomChanged_3(bool &state), onZoomChanged_4(bool &state);
  
    /*--- assets functions ----*/
    bool seekBarAreaIs(int x, int y);
    void manipulateZooms(int sectionNum, bool &state);
    void forceFalsedZoomFlags(int sectionNum);
    void checkingZoomOn();
    int  current_zoom_num;
  

  
};






