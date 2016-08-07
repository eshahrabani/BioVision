#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Marquee.h"
#include "MouseHandler.h"
#include "KeyHandler.h"


class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

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
		
		// GUI listener methods.
		void load();                           // Listens to the Load button.	
		void play_toggled(bool &b);            // Listens to the Play toggle button.
		void play_or_pause();		           // Global app method for playing or pausing the video.
		void next_frame();					   // Listens to the next frame button.
		void previous_frame();				   // Listens to the previous frame button.
		void play_speed_changed(float &f);	   // Listens to the play speed slider. 

		// Helper methods.
		void resizeVideoPlayer();
		void updateDimensions(int w, int h);

		// GUI components.
		ofxPanel gui;							 // Main interface panel.
		
		ofxButton load_button;					 // Load button.
		ofParameter<bool> play_toggle;			 // Play/Pause toggle.
		
		ofxButton next_frame_button;		     // Next frame button.
		ofxButton previous_frame_button;		 // Previous frame button.
		ofxSlider<float> play_speed;			 // Play speed slider.
		
		ofVideoPlayer video_player;				 // Video player.
		Marquee marquee;						 // Marquee for selecting regions of the video player.

		// Globals.
		int app_width = ofGetWidth();					  // Store the width of the app.
		int app_height = ofGetHeight();				      // Store the height of the app.
		
		int vid_width = app_width / 2;					  // Calculate the desired width of the video.
		int vid_height = app_height / 2;				  // Calculate the desired height of the video.
		int vid_x = app_width / 2 - vid_width / 2;	      // Calculate the left-corner x position of the video.
		int vid_y = app_height / 2 - vid_height / 2;      // Calculate the left-corner y position of the video.

		// Handlers. 
		MouseHandler* mouseHandler;
		KeyHandler* keyHandler;
};
