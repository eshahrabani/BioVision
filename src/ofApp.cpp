#include "ofApp.h"

// Constructor.
ofApp::ofApp() : ofBaseApp() {
	// Start handlers. 
	mouseHandler = new MouseHandler(this);
	keyHandler = new KeyHandler(this);
}

// Destructor.
ofApp::~ofApp() {
	// Delete the handlers.
	delete mouseHandler;
	delete keyHandler;
}

//--------------------------------------------------------------
// Called once on startup. 
void ofApp::setup(){
	// Start the main gui panel.
	gui.setup("BioVision");

	// Add the video buttons. 
	gui.add(load_button.setup("Load"));		
	
	// Add the play toggle, start it at paused (false). 
	gui.add(play_toggle.set("Play", false));						  
	gui.add(next_frame_button.setup("Next frame"));				      
	gui.add(previous_frame_button.setup("Previous frame"));		
	
	// Add the play speed slider, default speed at 1x, min at -3x, 
	// and max at 3x.
	gui.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));		  

	// Add the frame slider, default frame is at 1, min at 1, 
	// and max at total frame number.
	gui.add(frame.setup("Frame", 1, 1, video_player.getTotalNumFrames())); 
	gui.add(analyze_toggle.set("Analyze", false));

	// Link the buttons to their respective methods.
	load_button.addListener(this, &ofApp::load);					 
	play_toggle.addListener(this, &ofApp::play_toggled);              
	next_frame_button.addListener(this, &ofApp::next_frame);		  
	previous_frame_button.addListener(this, &ofApp::previous_frame);  
	play_speed.addListener(this, &ofApp::play_speed_changed);	      
	frame.addListener(this, &ofApp::frame_changed);
	analyze_toggle.addListener(this, &ofApp::analyze_toggled);

	// Setup computer vision.
	float w = vid_width;
	float h = vid_height;

	bLearnBackground = true;
	colorImg.allocate(w, h);
	grayImage.allocate(w, h);
	grayBg.allocate(w, h);
	grayDiff.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::update(){
	// Update the frames of the video player.
	video_player.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw the gui and its components.
	gui.draw();

	// Draw the video player according to current dimensions.
	video_player.draw(vid_x, vid_y, vid_width, vid_height);

	// Draw the marquee.
	marquee.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyHandler->handlePressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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
// When we detect the window has been resized, call updateDimensions() 
// to update all of our components that need to be updated.
void ofApp::windowResized(int w, int h){
	updateDimensions(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::load() {
	// Open load dialog.
	ofFileDialogResult result = ofSystemLoadDialog();							
	cout << "Attempting to load file: " << result.filePath << endl << endl;	

	// Attempt to load the file. Will refuse to load if the file extension 
	// is invalid, and notifies the user in the console. 
	video_player.loadMovie(result.filePath);											
	
	// Check successful load.
	if (video_player.isLoaded())
		cout << "File loaded successfully.\n\n";
	// Return otherwise. 
	else 
		return;

	// Unreachable if the video did not load properly. 
	// Displays the first frame.
	video_player.setPaused(true);
}


// This method is called when the state of the play toggle is changed,
// either graphically or via code. 
void ofApp::play_toggled(bool &play) {
	if (video_player.isLoaded()) {
		if (play) {
			// If the play toggle is enabled, play the video 
			// and change the toggle name to "Playing".
			video_player.setPaused(false);
			play_toggle.setName("Playing");
			cout << "Playing video.\n\n";  
		} else {
			// If the play toggle is disabled, pause the video 
			// and change the toggle name to "Play".
			video_player.setPaused(true);
			play_toggle.setName("Play");
			cout << "Pausing video.\n\n";
		}
	} else { 
		// File has not been loaded.
		if (play) {
			// If the play toggle is currently on, turn it back off.
			cout << "Load a video before playing.\n\n";
			play_toggle = !play_toggle;
		}
	}
}

// This method is used to either play or pause the video by inverting 
// the state of the play toggle, which is being listened to by play_toggled().
// This also updates the GUI.
void ofApp::play_or_pause() {
	play_toggle = !play_toggle;
}

void ofApp::next_frame() {
	// Exit method if video isn't loaded.
	if (!video_player.isLoaded()) 
		return;

	// If video is currently playing, pause it.
	if (play_toggle) {
		cout << "Pausing video.\n\n";
		play_or_pause();
	}

	// Go one frame forward.
	cout << "Going forward one frame.\n\n";
	if (frame < video_player.getTotalNumFrames()) 
		frame = frame + 1;
}

void ofApp::previous_frame() {
	// Exit method if video isn't loaded.
	if (!video_player.isLoaded()) 
		return;

	// If video is currently playing, pause it.
	if (play_toggle) {
		cout << "Pausing video.\n\n";
		play_or_pause();
	}

	// Go one frame backward.
	cout << "Going backward one frame.\n\n";
	if (frame > 1) 
		frame = frame - 1;
}

void ofApp::play_speed_changed(float &f) {
	if (!video_player.isLoaded()) 
		return;
	video_player.setSpeed(f);
}

void ofApp::frame_changed(int &frame) {
	if (!video_player.isLoaded()) 
		return;
	video_player.setFrame(frame);
}

void ofApp::analyze_toggled(bool &b) {
	// If video isn't loaded, exit this method after reverting the toggle 
	// (if it's on). 
	if (!video_player.isLoaded()) {
		if (b) 
			analyze_toggle = !analyze_toggle;
		return;
	}
	
	// If toggle is on, change the analyze toggle name to "analyzing"
	// and pause the video if it's currently playing. 
	if (b) {
		analyze_toggle.setName("Analyzing");
		cout << "Performing computer vision analysis.\n\n";
		if (play_toggle) 
			play_or_pause();
	} else
		analyze_toggle.setName("Analyze");

	// Computer vision analysis.
	colorImg.setFromPixels(video_player.getPixels());
	colorImg.setROI(0, 0, vid_width, vid_height);
	grayImage.setROI(0, 0, vid_width, vid_height);
	grayImage = colorImg;
	if (bLearnBackground) {
		grayBg = grayImage;
		bLearnBackground = false;
	}
	grayDiff.absDiff(grayBg, grayImage);
	grayDiff.threshold(30);
	contourFinder.findContours(grayDiff, 5, (340 * 240) / 4, 4, false, true);
	ofSetHexColor(0xffffff);
	colorImg.draw(0, 0, 320, 240);
	grayDiff.draw(0, 240, 320, 240);
	ofDrawRectangle(320, 0, 320, 240);
	contourFinder.draw(320, 0, 320, 240);
	ofColor c(255, 255, 255);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		r.x += 320; r.y += 240;
		c.setHsb(i * 64, 255, 255);
		ofSetColor(c);
		ofDrawRectangle(r);
	}
	cout << "Finished analysis.\n\n";
}

// Updates the size of the video player according to the current dimensions of the app.
void ofApp::resizeVideoPlayer() {
	vid_width = app_width / 2;					  
	vid_height = app_height / 2;				  
	vid_x = app_width / 2 - vid_width / 2;	      
	vid_y = app_height / 2 - vid_height / 2;      
}

// Updates the app to accomodate a new window size.
// Later: handle the resizing of other components besides the video player.
void ofApp::updateDimensions(int w, int h) {
	
	// Store the new width and height of the app in our global variables.
	app_width = w;					  
	app_height = h;	
	
	// Update the size of the video player.
	resizeVideoPlayer();
}

