// ofApp is the main class of this application. 
// It encapsulates the methods of the Timeline, so 
// all functionality should be routed through ofApp.

#pragma once

#include <math.h>
#include <random>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "Logger.h"
#include "Timeline.h"
#include "Marquee.h"
#include "MouseHandler.h"
#include "KeyHandler.h"


class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

		// Some user config:
		LoggerLevel loggerLevel = LoggerLevel::VERBOSE;

		// Default event methods.
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo); 
		void gotMessage(ofMessage msg);

		// GUI components.
		ofxPanel gui;							 
		
		ofxButton load_button;					
		ofParameter<bool> play_toggle;			
		
		ofxButton next_frame_button;		     
		ofxButton previous_frame_button;		 
		ofxSlider<float> play_speed;			 
		
		ofParameter<bool> analyze_toggle;		  
	
		Timeline* timeline;
		Marquee marquee;		

		ofImage playButtonImg;
		ofImage pauseButtonImg;
		ofImage stopButtonImg;

		// GUI listener methods.
		void load();
		void play_toggled(bool &b);
		void play_speed_changed(float &f);
		void analyze_toggled(bool &b);

		// Handlers. 
		MouseHandler* mouseHandler;
		KeyHandler* keyHandler;

		// Vision analysis.
		// TODO: restructure. 
		bool bLearnBackground;
		ofxCvContourFinder contourFinder;
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImage, threshold, grayBg, grayDiff;
		std::vector<ofPolyline> polylines;

		// Video controls.
		void play();
		void pause();
		void next_frame();
		void previous_frame();
		bool isVideoLoaded();
		bool isVideoPlaying();
		void setFrame(int);
		void setFrameFromMouseX(float);
		void restartVideo();

		// Helper methods. 
		bool isInsideTimeline(float, float);
		void resizeVideoPlayer();
		void updateDimensions(int w, int h);

		// Logger.
		Logger logger = Logger(loggerLevel);

		// Globals.
		int app_width = ofGetWidth();					  
		int app_height = ofGetHeight();		
		
		int vid_width = app_width / 2;					
		int vid_height = app_height / 2;				  
		//int vid_x = app_width / 2 - vid_width / 2;	   
		int vid_x = 0;
		int vid_y = app_height / 2 - vid_height / 2;

		int playButtonImgWidth = vid_width / 4;
		int playButtonImgHeight = app_height / 12;
		int playButtonImgX = app_width / 2;
		int playButtonImgY = (3 * app_height) / 4;

		// Constants.
		// Note: filenames are relative to the bin/data/ directory. 
		const string playButtonPath = "gui/PlayButton.jpg";
		const string pauseButtonPath = "gui/PauseButton.jpg";
		const string stopButtonPath = "gui/PauseButton.jpg";
};
