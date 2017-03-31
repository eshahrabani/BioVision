#include "ofApp.h"

// Constructor.
ofApp::ofApp() : ofBaseApp() {
	logger.writeVerbose("Running ofApp constructor.");

	// Start handlers. 
	mouseHandler = new MouseHandler(this);
	keyHandler = new KeyHandler(this);
}

// Destructor.
ofApp::~ofApp() {
	logger.writeVerbose("Running ofApp destructor.");

	// Delete the handlers.
	delete mouseHandler;
	delete keyHandler;

	// Delete the timeline.
	delete timeline;
}

//--------------------------------------------------------------
// Called once on startup. 
void ofApp::setup(){
	logger.writeVerbose("Running ofApp setup method.");

	// Store app width and height.
	app_width = ofGetWidth();
	app_height = ofGetHeight();
	updateDimensions(app_width, app_height);

	// Start the main gui panel.
	mainPanel.setup("BioVision");

	// Add video buttons. 
	mainPanel.add(load_button.setup("Load"));	
	mainPanel.add(play_toggle.set("Play", false));						  
	mainPanel.add(next_frame_button.setup("Next frame"));				      
	mainPanel.add(previous_frame_button.setup("Previous frame"));		
	mainPanel.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));		  
	
	// Add the analyze toggle.
	mainPanel.add(analyze_toggle.set("Analyze", false));

	// Link the buttons to their respective methods.
	load_button.addListener(this, &ofApp::load);					 
	play_toggle.addListener(this, &ofApp::play_toggled);              
	next_frame_button.addListener(this, &ofApp::next_frame);		  
	previous_frame_button.addListener(this, &ofApp::previous_frame);  
	play_speed.addListener(this, &ofApp::play_speed_changed);	      
	analyze_toggle.addListener(this, &ofApp::analyze_toggled);

	// Setup timeline.
	float tX = vid_x;
	float tY = vid_y + vid_height;
	float tWidth = vid_width;
	float tHeight = vid_height / 4;
	timeline = new Timeline(vid_x, vid_y, vid_width, vid_height,
		tX, tY, tWidth, tHeight,
		ofColor(67, 80, 102), 100);
}

//--------------------------------------------------------------
void ofApp::update(){
	timeline->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);

	// Draw the gui and its components.
	mainPanel.draw();

	// Draw the timeline.
	timeline->draw();

	// Draw the analysis area.
	ofSetColor(0, 0, 0);
	ofDrawRectangle(vid_x + vid_width, vid_y, vid_width, vid_height);
	
	// Draw the blobs found by the contour finder.
	ofSetColor(66, 244, 170);
	
	if (contourFinder.nBlobs > 0) {
		contours = blobsToPolylines(contourFinder.blobs);
	}
	for (ofPolyline p : contours) {
		drawPolyline(p, vid_x, vid_y);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyHandler->handlePressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	keyHandler->handleReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouseHandler->handleMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	mouseHandler->handleDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouseHandler->handlePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouseHandler->handleReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	
}

//--------------------------------------------------------------
// When we detect the window has been resized, call updateDimensions 
// to update all of our components that need to be updated.
void ofApp::windowResized(int w, int h){
	logger.writeVerbose(
		"Detected window resize. Updating dimensions of components."
	);
	updateDimensions(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

bool ofApp::isInsideTimeline(float x, float y) {
	return timeline->isInsideTimeline(x, y);
}

void ofApp::updateDimensions(int w, int h) {
	logger.writeVerbose("Updating dimensions.");
	// Store the new width and height of the app in our global variables.
	app_width = w;					  
	app_height = h;	

	vid_width = app_width / 2;
	vid_height = app_height / 2;
	vid_x = 0;
	vid_y = app_height / 2 - vid_height / 2;
}