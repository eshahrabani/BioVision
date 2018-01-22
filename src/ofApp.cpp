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

	// Close the output file.
	output.close();
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
	toolsPanel.setup("Analysis Controls");

	// Add video buttons. 
	mainPanel.add(load_button.setup("Load"));	
	mainPanel.add(play_toggle.set("Play", false));						  
	mainPanel.add(next_frame_button.setup("Next frame"));				      
	mainPanel.add(previous_frame_button.setup("Previous frame"));		
	mainPanel.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));
	mainPanel.setPosition(0, 0);

	toolsPanel.setDefaultWidth(250);
	toolsPanel.setPosition(this->app_width - 250, 0);
	toolsPanel.add(analyze_toggle.set("Analyze (beta)", false));
	toolsPanel.add(thresholdBlockSizeSlider.setup("Threshold block size", this->blockSize, 3, 100));
	toolsPanel.add(minBlobAreaSlider.setup("Minimum object area", 1, 1, vid_width * vid_height));
	toolsPanel.add(maxBlobAreaSlider.setup("Maximum object area", vid_width * vid_height, 1, vid_width * vid_height));
	toolsPanel.add(nMaxBlobsSlider.setup("Maximum number of objects", 5, 1, 100));
	toolsPanel.add(findHolesToggle.set("Find holes", false));
	toolsPanel.add(dilateToggle.set("Dilate", false));
	toolsPanel.add(erodeToggle.set("Erode", false));
	toolsPanel.add(polygonSelectorToggle.set("Polygon Selector Tool", false));
	toolsPanel.add(saveFrameButton.setup("Save Frame"));

	maxBlobAreaSlider.setDefaultWidth(250);

	// Link the buttons to their respective methods.
	load_button.addListener(this, &ofApp::load);					 
	play_toggle.addListener(this, &ofApp::play_toggled);              
	next_frame_button.addListener(this, &ofApp::next_frame);		  
	previous_frame_button.addListener(this, &ofApp::previous_frame);  
	play_speed.addListener(this, &ofApp::play_speed_changed);	      
	
	analyze_toggle.addListener(this, &ofApp::analyze_toggled);
	thresholdBlockSizeSlider.addListener(this, &ofApp::thresholdBlockSizeChanged);
	minBlobAreaSlider.addListener(this, &ofApp::minBlobAreaSliderChanged);
	maxBlobAreaSlider.addListener(this, &ofApp::maxBlobAreaSliderChanged);
	nMaxBlobsSlider.addListener(this, &ofApp::nMaxBlobsSliderChanged);
	findHolesToggle.addListener(this, &ofApp::findHolesToggled);
	dilateToggle.addListener(this, &ofApp::dilateToggled);
	erodeToggle.addListener(this, &ofApp::erodeToggled);
	polygonSelectorToggle.addListener(this, &ofApp::polygonSelectorToggled);
	saveFrameButton.addListener(this, &ofApp::saveFrame);

	// Setup timeline.
	float tX = vid_x;
	float tY = vid_y + vid_height;
	float tWidth = vid_width;
	float tHeight = vid_height / 4;
	timeline = new Timeline(vid_x, vid_y, vid_width, vid_height,
		tX, tY, tWidth, tHeight,
		ofColor(67, 80, 102), 100);
	
	output.open("data/output.txt");
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
	toolsPanel.draw();

	// Draw the timeline and a label above it.
	timeline->draw();
	
	float labelX = vid_x + (vid_width / 2);
	float labelY = vid_y - 10.0;
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Video", labelX, labelY);

	// Draw the analysis area and a label above it.
	ofSetColor(0, 0, 0);
	ofDrawRectangle(vid_x + vid_width, vid_y, vid_width, vid_height);

	// Draw the thresholded image if it's been allocated.
	if (this->threshold.bAllocated) {
		ofSetColor(255, 255, 255);
		this->threshold.draw(vid_x + vid_width, vid_y, vid_width, vid_height);
	}

	labelX = vid_x + vid_width + (vid_width / 2);
	labelY = vid_y - 10.0;
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Analysis", labelX, labelY);
	
	// Draw the contours found by the contour finder.
	if (contourFinder.nBlobs > 0) {
		ofSetColor(255, 0, 0);

		// Use (vid_x, vid_y) as the anchor point to draw the contours.
		//drawPolylines(contours, vid_x + vid_width, vid_y);
		/*for (ofPolyline p : contours) {
			p.draw();
		}*/
		logger.writeNormal(std::to_string(contourFinder.nBlobs) + " blobs found.");
		contourFinder.draw(vid_x + vid_width, vid_y, vid_width, vid_height);
	}

	// Draw the selected area.
	ofSetColor(255, 0, 0);
	selectedArea.draw();

	// Draw all selected objects.
	ofSetColor(66, 117, 238);
	for (ofPolyline p : selectedAreas) {
		p.draw();
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

	// Video width should always be half of app width.
	vid_width = app_width / 2;

	// Video height should always be half of app height.
	vid_height = app_height / 2;

	// Video x position should always be on the left.
	vid_x = 0;

	// Video y position should always be at 1/3 of the height.
	vid_y = app_height / 3; 
}