#include "KeyHandler.h"
#include "ofApp.h"

KeyHandler::KeyHandler(ofApp* app) {

	// Copies the address from app to this->app.
	this->app = app;
}

void KeyHandler::handlePressed(int key) {
	switch (key) {

	// If p is pressed, play or pause the video.
	case 'P':
	case 'p':
		app->play_or_pause();
		break;

	// If l is pressed, open the load dialog.
	case 'L':
	case 'l':
		app->load();
		break;

	// Move forward one frame if CTRL+RIGHT are pressed.
	case OF_KEY_RIGHT:
		right_pressed = true;	

		// This not executed if RIGHT is pressed first. 
		// SEE: case OF_KEY_CONTROL for opposite condition. 
		if (ctrl_pressed) app->next_frame();   					 
		break;

	// Same implementation as case OF_KEY_RIGHT. 
	case OF_KEY_LEFT:
		left_pressed = true;
		if (ctrl_pressed) app->previous_frame();
		break;

	// If f is pressed, increase play speed by 0.25.
	case 'F':
	case 'f': 
	{
		// Reference var to the speed slider. 
		ofxSlider<float>& speed = app->play_speed;

		// Check boundaries. 
		if ((speed + 0.25) <= speed.getMax()) {
			speed = speed + 0.25;
			cout << "Increasing speed by 0.25.\n\n";
		}
		else cout << "Maximum speed already hit.\n\n";
	}
		break;

	// Same implementation as case 'f'.
	case 'R':
	case 'r':
	{
		// Reference var to the speed slider.
		ofxSlider<float>& speed = app->play_speed;

		// Check boundaries. 
		if ((speed - 0.25) >= speed.getMin()) {
			speed = speed - 0.25;
			cout << "Decreasing speed by 0.25.\n\n";
		}
		else cout << "Minimum speed already hit.\n\n";
	}
		break;

	// If m is pressed, clear the marquee. 
	case 'M':
	case 'm':
		cout << "Clearing marquee.\n\n";
		app->marquee.clear();
		break;

	// If RIGHT+CTRL or LEFT+CTRL is pressed, move forward/backward one frame. 
	case OF_KEY_CONTROL:
		ctrl_pressed = true;

		// These are not executed if CTRL is pressed first.
		// SEE: case OF_RIGHT_PRESSED and case OF_LEFT_PRESSED for opposite condition. 
		if (right_pressed) app->next_frame();
		if (left_pressed) app->previous_frame();
		break;

	case OF_KEY_ALT:
		alt_pressed = true;
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

	// TODO: Implement default case. 
	}
}

void KeyHandler::handleReleased(int key) {
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
	}
}

