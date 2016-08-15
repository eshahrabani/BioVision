#include "ofApp.h"

// Constructor.
ofApp::ofApp() : ofBaseApp() {

	// Start handlers. 
	mouseHandler = new MouseHandler(this);
	keyHandler = new KeyHandler(this);
}

// Destructor.
ofApp::~ofApp() {
	delete mouseHandler;
	delete keyHandler;
}

//--------------------------------------------------------------
// Called once on startup. 
void ofApp::setup(){
	
	// Start the gui panel.
	gui.setup("BioVision");

	// Add the video buttons. 
	gui.add(load_button.setup("Load"));							      // Add the Load button.
	gui.add(play_toggle.set("Play", false));						  // Add the play/pause toggle and start it at false (paused). 
	gui.add(next_frame_button.setup("Next frame"));				      // Add the next frame button.
	gui.add(previous_frame_button.setup("Previous frame"));			  // Add the previous frame button.
	gui.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));		  // Add the play speed slider, default speed at 1x, min at -3x, and max at 3x.
	gui.add(frame.setup("Frame", 1, 1, video_player.getTotalNumFrames())); // Add the frame slider, default frame is at 1, min at 1, and max at total frame number.

	// Link the buttons to their respective methods.
	load_button.addListener(this, &ofApp::load);					  // Link the Load button to the load method.
	play_toggle.addListener(this, &ofApp::play_toggled);              // Link the play toggle to the play_toggled method.
	next_frame_button.addListener(this, &ofApp::next_frame);		  // Link the next frame button to the next_frame method.
	previous_frame_button.addListener(this, &ofApp::previous_frame);  // Link the previous frame button to the previous_frame method. 
	play_speed.addListener(this, &ofApp::play_speed_changed);	      // Link the play speed slider to the play_speed_changed method.
	frame.addListener(this, &ofApp::frame_changed);
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
// When we detect the window has been resized, call the updateDimensions() method to update all of our components that need to be updated.
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
	cout << "Attempting to load file: " << result.filePath << endl << endl;;	

	// Attempt to load the file. 
	// Will refuse to load if the file extension is invalid, and notifies the user.
	video_player.loadMovie(result.filePath);											
	
	// Check successful load.
	if (video_player.isLoaded()) {
		cout << "File loaded successfully.\n\n";
	}
	else return;

	// Displays the first frame.
	video_player.setPaused(true);
}


// This method is triggered when the state of the play toggle is changed, either graphically or via code. 
void ofApp::play_toggled(bool &play) {

	// If the file has been loaded...
	if (video_player.isLoaded()) {

		// If the play toggle is currently enabled, play the video and change the toggle name to "Playing".
		if (play) {
			video_player.setPaused(false);
			play_toggle.setName("Playing");
			cout << "Playing video.\n\n";  
		}

		// If the play toggle is currently disabled, pause the video and change the toggle name to "Play".
		else {
			video_player.setPaused(true);
			play_toggle.setName("Play");
			cout << "Pausing video.\n\n";
		}
	}

	// If the file has not been loaded...
	else {

		// If the play toggle is currently on, turn it back off.
		if (play) {
			cout << "Load a video before playing.\n\n";
			play_toggle = !play_toggle;
		}
	}
}

// This method is used to either play or pause the video by inverting the state of the play toggle, which is being listened to by play_toggled().
// This also updates the GUI.
void ofApp::play_or_pause() {
	play_toggle = !play_toggle;
}

void ofApp::next_frame() {

	// Exit method if video isn't loaded.
	if (!video_player.isLoaded()) {
		return;
	}

	// If video is currently playing, pause it.
	if (play_toggle) {
		cout << "Pausing video.\n\n";
		play_or_pause();
	}

	// Go one frame forward.
	cout << "Going forward one frame.\n\n";
	if (frame < video_player.getTotalNumFrames()) {
		frame = frame + 1;
	}
}

void ofApp::previous_frame() {

	// Exit method if video isn't loaded.
	if (!video_player.isLoaded()) {
		return;
	}

	// If video is currently playing, pause it.
	if (play_toggle) {
		cout << "Pausing video.\n\n";
		play_or_pause();
	}

	// Go one frame backward.
	cout << "Going backward one frame.\n\n";
	if (frame > 1) {
		frame = frame - 1;
	}
}

void ofApp::play_speed_changed(float &f) {
	if (!video_player.isLoaded()) return;
	video_player.setSpeed(f);
}

void ofApp::frame_changed(int &frame) {
	if (!video_player.isLoaded()) return;
	video_player.setFrame(frame);
}

// Updates the size of the video player according to the current dimensions of the app.
void ofApp::resizeVideoPlayer() {
	vid_width = app_width / 2;					  // Calculate the desired width of the video.
	vid_height = app_height / 2;				  // Calculate the desired height of the video.
	vid_x = app_width / 2 - vid_width / 2;	      // Calculate the left-corner x position of the video.
	vid_y = app_height / 2 - vid_height / 2;      // Calculate the left-corner y position of the video.
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

