#pragma once

#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "KnownObjectsPanel.h"
#include "DetectedObject.h"
#include "Logger.h"
#include "Timeline.h"
#include "Marquee.h"
#include "MouseHandler.h"
#include "KeyHandler.h"
#include "functions.h"

using std::vector;
using std::ofstream;

// ofApp is the main class of this application. 
// It encapsulates the methods of the Timeline, so 
// all functionality should be routed through ofApp.
class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

		/* -------------------- LOGGER CONFIGURATION --------------------*/
		LoggerLevel loggerLevel = LoggerLevel::VERBOSE;
		Logger logger = Logger(loggerLevel);


		/* -------------------- LIFECYCLE METHODS AND EVENT LISTENERS --------------------*/

		// Setup() is called on initiation of ofApp, only once.
		void setup();
		
		// update() is called many times per second, always preceding draw(). 
		void update();

		// draw() is called many timers per second, always succeeding update().
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


		/* -------------------- GUI COMPONENTS --------------------*/
		
		// The main panel consisting of the load button, etc. 
		ofxPanel mainPanel;		

		// Panel for tracking known objects.
		KnownObjectsPanel knownObjectsPanel;

		ofxPanel toolsPanel;

		ofxPanel objectsPanel;
		
		// The load button on the main panel.
		ofxButton load_button;			

		// The play toggle on the main panel.
		ofParameter<bool> play_toggle;			
		
		// The next frame button on the main panel.
		ofxButton next_frame_button;		  

		// The previous frame button on the main panel.
		ofxButton previous_frame_button;	

		// The play speed slider on the main panel.
		ofxSlider<float> play_speed;	

		// Create objects button.
		ofxButton createObjectsButton;

		// Mark as known object button.
		ofxButton markObjectButton;

		// Select object toggle.
		ofParameter<bool> selectObjectToggle;

		// Consolidate selected objects button.
		ofxButton consolidateObjectsButton;

		// Separate object button.
		ofxButton separateObjectButton;

		// Delete selected object button.
		ofxButton deleteObjectButton;
		
		// The analyze toggle on the analysis panel.
		ofParameter<bool> analyze_toggle;		

		// Threshold block size slider.
		ofxSlider<int> thresholdBlockSizeSlider;

		// Minimum blob area slider.
		ofxSlider<int> minBlobAreaSlider;

		// Maximum blob area slider.
		ofxSlider<int> maxBlobAreaSlider;

		// Maximum number of blobs slider.
		ofxSlider<int> nMaxBlobsSlider;

		// Find holes toggle.
		ofParameter<bool> findHolesToggle;

		// Dilate toggle.
		ofParameter<bool> dilateToggle;

		// Erode toggle.
		ofParameter<bool> erodeToggle;

		// The polygon selector toggle on the main panel.
		ofParameter<bool> polygonSelectorToggle;

		// Clear polygons button.
		ofxButton clearPolygonsButton;

		// Output mode toggle.
		ofParameter<bool> outputModeToggle;

		// Save frame button.
		ofxButton saveFrameButton;
	
		// The timeline component.
		Timeline* timeline;

		// The marquee component. 
		Marquee marquee;		


		/* -------------------- GUI LISTENERS --------------------*/
		
		// The function attached to the load button.
		void load();

		// The function attached to the play toggle.
		void play_toggled(bool &b);

		// The function attached to the play slider.
		void play_speed_changed(float &f);

		void createObjectPressed();
		void markObjectPressed();
		void markedObjectPressed(string name);
		void selectObjectToggled(bool &b);
		void consolidateObjectsPressed();
		void separateObjectPressed();
		void deleteObjectPressed();

		// The function attached to the analyze toggle.
		void analyze_toggled(bool &b);

		// The function attached to the threshold block size slider.
		void thresholdBlockSizeChanged(int &blockSize);

		void minBlobAreaSliderChanged(int &area);
		void maxBlobAreaSliderChanged(int &area);
		void nMaxBlobsSliderChanged(int &n);
		void findHolesToggled(bool &b);

		void dilateToggled(bool &b);
		void erodeToggled(bool &b);

		// The function attached to the polygon selector toggle.
		void polygonSelectorToggled(bool &b);

		// Output mode toggle listener.
		void outputModeToggled(bool &b);

		// Save frame button listener.
		void saveFrame();


		/* -------------------- VISION ANALYSIS -------------------- */
		bool bLearnBackground;
		ofxCvContourFinder contourFinder;
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImage, threshold, grayBg, grayDiff;
		vector<ofPolyline> contours; 
		vector<DetectedObject> detectedObjects;
		vector<DetectedObject*> selectedObjects; // Contains pointers to objects in detectedObjects vector.

		/* -------------------- VIDEO CONTROLS -------------------- */
		
		// Play the timeline video.
		void play();

		// Pause the timeline video.
		void pause();

		// Go to the next frame in the video.
		void next_frame();

		// Go to the previous frame in the video.
		void previous_frame();

		// Check if the timeline video is loaded.
		bool isVideoLoaded();

		// Check if the timeline video is playing. 
		bool isVideoPlaying();

		// Set the frame of the video.
		void setFrame(int);

		// Get the current frame of the video.
		int getCurrentFrame();

		// Set the frame of the video using the position of a click on 
		// the timeline. 
		void setFrameFromMouseX(float);

		// Restart the timeline video. 
		void restartVideo();


		/* -------------------- I/O HANDLERS -------------------- */

		// Controls all mouse events for ofApp.
		MouseHandler* mouseHandler;

		// Controls all key events for ofApp.
		KeyHandler* keyHandler;


		/* -------------------- GLOBAL VARIABLES -------------------- */

		// The width of the app.
		int app_width;			

		// The height of the app.
		int app_height;		
		
		// The width of the video.
		int vid_width;				

		// The height of the video.
		int vid_height;				

		// The x coordinate of the video relative to the app. 
		int vid_x;

		// The y coordinate of the video relative to the app.
		int vid_y;

		// The state of the polygon selector tool.
		bool polygonSelection = false;

		// The currently selected area via the polygon selector tool.
		ofPolyline selectedArea;

		// All the objects selected for the current frame.
		std::vector<ofPolyline> selectedAreas;

		bool bAnalyze = false;
		int blockSize = 3;

		ofstream output;

		/* -------------------- HELPER METHODS -------------------- */

		void analyze(bool doThreshold=true);

		// Check if a point is inside the timeline. 
		bool isInsideTimeline(float, float);

		// Update the dimensions of ofApp. 
		void updateDimensions(int w, int h);
};