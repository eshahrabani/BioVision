#include "MouseHandler.h"
#include "ofApp.h"

MouseHandler::MouseHandler(ofApp* app) {
	this->app = app;
}

void MouseHandler::handleMoved(int x, int y) {
	pos_x = x;
	pos_y = y;
}

void MouseHandler::handleDragged(int x, int y, int button) {
	// Handle the mouse movement first. 
	handleMoved(x, y);

	// If control is pressed, draw a marquee.
	if (button == OF_MOUSE_BUTTON_LEFT && app->keyHandler->ctrl_pressed && pressed_inside_player) {
		if (app->video_player.isLoaded()) {
			app->marquee.setFromDrag(last_clicked_x, last_clicked_y, x, y);
		}
	}
}

void MouseHandler::handlePressed(int x, int y, int button) {
	last_clicked_x = x;
	last_clicked_y = y;
	last_clicked_button = button;

	if (button == OF_MOUSE_BUTTON_LEFT) {

		// TODO: Needs streamline via custom videoplayer class. 
		ofRectangle area;
		area.set(app->vid_x, app->vid_y, app->vid_width, app->vid_height);

		if (area.inside(x, y)) {
			pressed_inside_player = true;
		}
	}
}

void MouseHandler::handleReleased(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT && pressed_inside_player) {
		pressed_inside_player = false;
	}
}