#include "KeyParser.h"

KeyParser::KeyParser(ofApp* app) {

	// Copies the address from app to this->app.
	this->app = app;
}

void KeyParser::parsePressed(int key) {
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

		// If the right arrow key is pressed, check to make sure control is pressed as well. 
		// If so, go forward one frame.
	case OF_KEY_RIGHT:
		right_pressed = true;				// Update the global right_pressed boolean in case control is pressed after this key is.
		if (ctrl_pressed) app->next_frame();		// Is not executed if control is pressed second, so we needed to update the boolean.								 
		break;

		// Same as right arrow key, but for the left now.
	case OF_KEY_LEFT:
		left_pressed = true;
		if (ctrl_pressed) app->previous_frame();
		break;

		// If f is pressed, increase play speed by 0.25.
	case 'F':
	case 'f':
		// Check slider max boundary.
		if ((app->play_speed + 0.25) <= app->play_speed.getMax()) {
			app->play_speed = app->play_speed + 0.25;
		}
		break;

		// If r is pressed, decrease play speed by 0.25.
	case 'R':
	case 'r':
		// Check slider min boundary.
		if ((app->play_speed - 0.25) >= app->play_speed.getMin()) {
			app->play_speed = app->play_speed - 0.25;
		}
		break;
	case 'M':
	case 'm':
		app->marquee.clear();
		break;

		// Set the global ctrl_pressed boolean to true.
	case OF_KEY_CONTROL:
		ctrl_pressed = true;
		if (right_pressed) app->next_frame();
		if (left_pressed) app->previous_frame();
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

void KeyParser::parseReleased(int key) {
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

