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
	if (button == OF_MOUSE_BUTTON_LEFT) {
		/*if (pressedInsidePlayer) {
			if (app->timeline->isVideoLoaded()) {

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
		
		}*/

		// If ctrl pressed, move contourfinder blobs.
		KeyHandler& kh = *(app->keyHandler);
		if (kh.ctrl_pressed && app->contours.size() > 0) {
			float dx = x - pos_x;
			float dy = y - pos_y;

			// Apply displacements to left corner of every point. 
			std::vector<ofPolyline>* contours = &(app->contours);
			for (int i = 0; i < contours->size(); i++) {
				// Store the polyline so we can modify it.
				ofPolyline p = (*contours)[i];

				for (int j = 0; j < p.size(); j++) {
					// Store the point so we can modify it.
					ofPoint pt = p[j];

					// Modify point then reassign back to the polyline.
					pt.x += dx;
					pt.y += dy;
					p[j] = ofPoint(pt);
				}
				// Reassign polyline back to polyline vector.
				(*contours)[i] = p;
			}
		}

		// If in timeline, update the frame position.
		if (pressedInsideTimeline) {
			// No need to pause since a click must have occured
			// on the timeline, during which the video is paused.
			app->setFrameFromMouseX(x);
		}
	}

	// Updates internal coordinates once we're done with them.
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
			pressedInsidePlayer = true;
		}

		if (app->isInsideTimeline(x, y) && app->isVideoLoaded()) {
			cout << "Clicked inside timeline.\n\n";
			pressedInsideTimeline = true;
			
			// Make sure video is paused.
			app->pause();
			cout << "Setting timeline frame with x coordinate: " << x << endl << endl;
			app->setFrameFromMouseX(x);
		}
	}
}

void MouseHandler::handleReleased(int x, int y, int button) {
	pressedInsidePlayer = false;
	pressedInsideTimeline = false;
}