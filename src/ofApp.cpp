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
	gui.setup("BioVision");

	// Add video buttons. 
	gui.add(load_button.setup("Load"));	
	gui.add(play_toggle.set("Play", false));						  
	gui.add(next_frame_button.setup("Next frame"));				      
	gui.add(previous_frame_button.setup("Previous frame"));		
	gui.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));		  
	
	// Add the analyze toggle.
	gui.add(analyze_toggle.set("Analyze", false));

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
	gui.draw();

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

void ofApp::load() {
	logger.writeVerbose("From ofApp: calling load() on timeline.");
	timeline->load();
}


// This method is called when the state of the play toggle is changed,
// either graphically or via code (play_toggle = !play_toggle).  
void ofApp::play_toggled(bool &play) {
	logger.writeVerbose("Play has been toggled.");
	if (timeline->isVideoLoaded()) {
		if (play) {
			// If the play toggle is enabled, play the video 
			// and change the toggle name to "Playing".
			this->play();
			play_toggle.setName("Playing");
			logger.writeNormal("Playing video.");
		} else {
			// If the play toggle is disabled, pause the video 
			// and change the toggle name to "Play".
			this->pause();
			play_toggle.setName("Play");
			logger.writeNormal("Pausing video.");
		}
	} else { 
		// File has not been loaded.
		if (play) {
			// If the play toggle is currently on, turn it back off.
			logger.writeNormal("Load a video before playing.");

			// Turns off the play toggle without recursively triggering 
			// the containing method (play_toggled).
			play_toggle.setWithoutEventNotifications(false);
		}
	}
}

void ofApp::play_speed_changed(float &f) {
	logger.writeVerbose("Setting new play speed from ofApp.");
	timeline->setVideoSpeed(f);
}

// TODO: needs encapsulation of analysis into 
// analyzer object. 
void ofApp::analyze_toggled(bool &b) {
	logger.writeVerbose("Analyze toggled.");

	// If video isn't loaded, exit this method after reverting the toggle 
	// (if it's on). 
	if (!timeline->isVideoLoaded()) {
		if (b) 
			analyze_toggle = !analyze_toggle;
		return;
	}
	
	// If toggle is on, change the analyze toggle name to "analyzing"
	// and pause the video if it's currently playing. 
	if (b) {
		analyze_toggle.setName("Analyzing");
		logger.writeNormal("Performing computer vision analysis.");
		if (play_toggle)
			timeline->pause();
	}
	else {
		analyze_toggle.setName("Analyze");

		// Don't perform any analysis if toggled off. 
		return;
	}

	float w = vid_width;
	float h = vid_height;

	bLearnBackground = true;
	colorImg.allocate(w, h);
	grayImage.allocate(w, h);
	grayBg.allocate(w, h);
	grayDiff.allocate(w, h);
	threshold.allocate(w, h);
	
	// Computer vision analysis.
	colorImg.setFromPixels(timeline->getVideoPixels());
	colorImg.setROI(0, 0, w, h);
	grayImage.setROI(0, 0, w, h);
	threshold.setROI(0, 0, w, h);
	grayImage = colorImg;
	threshold = grayImage;
	threshold.threshold(100);
	contourFinder.findContours(threshold, 5, vid_width * vid_height, 10, 
		false, false);

	logger.writeNormal("Finished vision analysis.");
}

void ofApp::play() {
	logger.writeVerbose("Playing the video.");

	// Turn the play toggle on without triggering play_toggled.
	play_toggle.setWithoutEventNotifications(true);
	timeline->play();
}

void ofApp::pause() {
	logger.writeVerbose("Pausing the video.");

	// Turn the play toggle off without triggering play_toggled.
	play_toggle.setWithoutEventNotifications(false);
	timeline->pause();
}

void ofApp::next_frame() {
	if (timeline->isVideoPlaying()) {
		logger.writeVerbose(
			"Video is playing; pausing it before jumping to next frame."
		);
		pause();
	}
	logger.writeVerbose("Jumping to next frame.");
	timeline->nextFrame();
}

void ofApp::previous_frame() {
	if (timeline->isVideoPlaying()) {
		pause();
	}
	timeline->previousFrame();
}

bool ofApp::isVideoLoaded() {
	return timeline->isVideoLoaded();
}

bool ofApp::isVideoPlaying() {
	return timeline->isVideoPlaying();
}

void ofApp::setFrame(int f) {
	logger.writeVerbose("Setting new frame from ofApp.");
	timeline->setFrame(f);
}

void ofApp::setFrameFromMouseX(float x) {
	logger.writeVerbose("Setting new frame from ofApp using mouse X.");
	timeline->setFrameFromMouseX(x);
}

void ofApp::restartVideo() {
	logger.writeVerbose("Restarting ofApp.");
	timeline->restartVideo();
}

bool ofApp::isInsideTimeline(float x, float y) {
	return timeline->isInsideTimeline(x, y);
}

// Updates the app to accomodate a new window size.
// Later: handle the resizing of other components besides the video player.
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