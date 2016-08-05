#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// Start the gui panel.
	gui.setup("BioVision");

	// Add the video buttons. 
	gui.add(load_button.setup("Load"));							      // Add the Load button.
	gui.add(play_toggle.set("Play", false));						  // Add the play/pause toggle and start it at false (paused). 
	gui.add(next_frame_button.setup("Next frame"));				      // Add the next frame button.
	gui.add(previous_frame_button.setup("Previous frame"));			  // Add the previous frame button.
	gui.add(play_speed.setup("Play speed", 1.0, -3.0, 3.0));		  // Add the play speed slider, default speed at 1x, min at -3x, and max at 3

	// Link the buttons to their respective methods.
	load_button.addListener(this, &ofApp::load);					  // Link the Load button to the load method.
	play_toggle.addListener(this, &ofApp::play_toggled);              // Link the play toggle to the play_toggled method.
	next_frame_button.addListener(this, &ofApp::next_frame);		  // Link the next frame button to the next_frame method.
	previous_frame_button.addListener(this, &ofApp::previous_frame);  // Link the previous frame button to the previous_frame method. 
	play_speed.addListener(this, &ofApp::play_speed_changed);	      // Link the play speed slider to the play_speed_changed method.
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

	// Draw the marqee if currently defined. 
	if (marquee != nullptr) {
		ofSetColor(192, 192, 192);
		ofNoFill();
		ofDrawRectangle(*marquee);
	} 
	else {
		ofSetColor(255, 255, 255);
		ofNoFill();
		ofDrawRectangle(0, 0, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {

		// If p is pressed, play or pause the video.
		case 'P':
		case 'p':
			play_or_pause();
			break;
		
		// If l is pressed, open the load dialog.
		case 'L':
		case 'l':
			load();
			break;
		
		// If the right arrow key is pressed, check to make sure control is pressed as well. 
		// If so, go forward one frame.
		case OF_KEY_RIGHT:
			right_pressed = true;				// Update the global right_pressed boolean in case control is pressed after this key is.
			if (ctrl_pressed) next_frame();		// Is not executed if control is pressed second, so we needed to update the boolean.								 
			break;

		// Same as right arrow key, but for the left now.
		case OF_KEY_LEFT:
			left_pressed = true;				
			if (ctrl_pressed) previous_frame();
			break;

		// If f is pressed, increase play speed by 0.25.
		case 'F':
		case 'f':
			// Check slider max boundary.
			if ((play_speed + 0.25) <= play_speed.getMax()) {
				play_speed = play_speed + 0.25;
			}
			break;

		// If r is pressed, decrease play speed by 0.25.
		case 'R':
		case 'r':
			// Check slider min boundary.
			if ((play_speed - 0.25) >= play_speed.getMin()) {
				play_speed = play_speed - 0.25;
			}
			break;
		case 'M':
		case 'm':
			m_pressed = true;
			if (marquee != nullptr) {
				cout << "Clearing marquee\n\n";
				delete marquee;
				marquee = nullptr;
			}
			break;

		// Set the global ctrl_pressed boolean to true.
		case OF_KEY_CONTROL:
			ctrl_pressed = true;
			if (right_pressed) next_frame();
			if (left_pressed) previous_frame();
			break;

		// If h is pressed, print handy key commands.
		case 'H':
		case 'h':
			cout << "p: play/pause\n";
			cout << "l: load\n";
			cout << "control + right: skip forward one frame\n";
			cout << "control + left: skip backward one frame\n";
			cout << "f: increase speed by 0.25\n";
			cout << "r: decrease speed by 0.25\n";
			cout << "control + left click & drag: draw marquee on video\n";
			cout << "control + m: clear marquee\n";
			cout << "h: help\n\n";
			break;

		// Tell the user how to access the help dialog.
		default:
			//cout << "Key command unrecognized. Press h for a list of valid commands.\n\n";
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
		
		// If the control key is released, set its global boolean to false.
		case OF_KEY_CONTROL:
			ctrl_pressed = false;
			break;

		// If the right arrow key is released, set its global boolean to false.
		case OF_KEY_RIGHT:
			right_pressed = false;
			break;

		// If the left arrow key is released, set its global boolean to false.
		case OF_KEY_LEFT:
			left_pressed = false;
			break;

		// If the m key is released, set its global boolean to false.
		case 'M':
		case 'm':
			m_pressed = false;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouse_x = x;
	mouse_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	// Trigger the mouseMoved(int,int) method first since it doesn't call if dragged.
	mouseMoved(x, y);

	// If control is pressed, draw a marquee.
	if (button == OF_MOUSE_BUTTON_LEFT && ctrl_pressed && pressed_inside_player) {
		// Find the midpoint of the marquee diagonal line.
		int x_center = (initial_x_inside + x) / 2;
		int y_center = (initial_y_inside + y) / 2;

		// Assuming 45 degree angles (square marquee): 2w^2 = d^2; w = sqrt(d^2 / 2).
		float d = sqrt(pow(x_center - initial_x_inside, 2) + pow(y_center - initial_y_inside, 2));	// Apply distance formula.
		int w, h;
		w = h = sqrt(pow(d, 2) / 2);

		// Clear previous marquee.
		if (marquee != nullptr) {
			delete marquee;
		}

		// Set new marquee.
		marquee = new ofRectangle();
		marquee->setFromCenter(x_center, y_center, w, h);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_LEFT) {
		ofRectangle area;
		area.set(vid_x, vid_y, vid_width, vid_height);

		if (area.inside(x, y)) {
			pressed_inside_player = true;
			initial_x_inside = x;
			initial_y_inside = y;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_LEFT && pressed_inside_player) {
		// Must now be false.
		pressed_inside_player = false;
	}
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
	ofFileDialogResult result = ofSystemLoadDialog();							// Store the user's selection.
	cout << "Attempting to load file: " << result.filePath << endl << endl;;	

	// Attempt to load the file. 
	// Will refuse to load if the file extension is invalid, and notifies the user.
	video_player.loadMovie(result.filePath);											// TODO: no error printing if no file is selected.
	
	// Check successful load.
	if (video_player.isLoaded()) {
		cout << "File loaded successfully.\n\n";
	}

	// Displays the first frame for user feedback.
	video_player.setPaused(true);
}


// This method is triggered when the state of the play toggle is changed, either graphically or via code. 
// NOTE: currently being called many times per second in update().
void ofApp::play_toggled(bool &play) {

	// If the file has been loaded...
	if (video_player.isLoaded()) {

		// If the play toggle is currently enabled, play the video and change the toggle name to "Playing".
		if (play) {
			video_player.setPaused(false);
			play_toggle.setName("Playing");
			cout << "Playing video.\n\n";   // Prints hundreds of times per second since this method is called in update().
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
// This is useful because it also updates the GUI.
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
	video_player.nextFrame();
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
	video_player.previousFrame();
}

void ofApp::play_speed_changed(float &f) {
	video_player.setSpeed(f);
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

