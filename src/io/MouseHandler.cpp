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

	// If control is pressed, draw a marquee.
	if (button == OF_MOUSE_BUTTON_LEFT && pressed_inside_player) {
		if (app->video_player.isLoaded()) {

			// Create marquee.
			if (app->keyHandler->ctrl_pressed) {
				app->marquee.setFromDrag(last_clicked_x, last_clicked_y, x, y);
			}

			// Move marquee.
			else if (app->keyHandler->alt_pressed) {

				// Calculate displacements from click position.
				int dx = x - pos_x;
				int dy = y - pos_y;

				// Apply displacement to left corner.
				int new_x = app->marquee.getX() + dx;
				int new_y = app->marquee.getY() + dy;
				app->marquee.set(new_x, new_y, app->marquee.width(), app->marquee.height());
			}
		}
	}

	handleMoved(x, y);
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