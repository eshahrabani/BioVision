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
		bool pressedInsideAnalysisArea = false;
		ofRectangle vidPlayerArea, analysisArea;
		vidPlayerArea.set(app->vid_x, app->vid_y, app->vid_width, app->vid_height);
		analysisArea.set(app->vid_x + app->vid_width, app->vid_y, app->vid_width, app->vid_height);

		if (vidPlayerArea.inside(x, y)) {
			this->pressedInsidePlayer = true;
		}

		if (analysisArea.inside(x, y)) {
			pressedInsideAnalysisArea = true;
		}

		if (app->isInsideTimeline(x, y) && app->isVideoLoaded()) {
			pressedInsideTimeline = true;
			
			// Make sure video is paused.
			app->pause();
			app->setFrameFromMouseX(x);
		}

		// If pressed inside player/analysis area and polygonSelection is true, build a polygon selection.
		if (app->polygonSelection && (pressedInsidePlayer || pressedInsideAnalysisArea)) {
			app->selectedArea.addVertex(x, y);
		}

		// If pressed inside an object, select that object.
		if (app->selectObjectToggle && app->detectedObjects.size() > 0) {
			DetectedObject* selectedObject = NULL;
			bool oneFound = false;

			// Iterate by reference.
			for (DetectedObject &obj : app->detectedObjects) {
				if (obj.containsPoint(ofPoint(x, y))) {
					// Store the address of the found object.
					selectedObject = &obj;
					oneFound = true;

					break;
				}
			}
			if (!oneFound) {
				// Find nearest within 15px then select it.
				float minDist = std::numeric_limits<float>::max();
				int minIndex = 0;
				int i = 0;
				for (DetectedObject &obj : app->detectedObjects) {
					ofPoint closestPoint = obj.getClosestPoint(ofPoint(x, y));
					float dist = abs(ofDist(x, y, closestPoint.x, closestPoint.y));

					if (minDist > dist) {
						minDist = dist;
						minIndex = i;
					}

					i++;
				}
				// Store the address of the found object.
				if (minDist < 15) {
					selectedObject = &app->detectedObjects.at(minIndex);
				}
			}
			// If selected object is not null (was found), and it is not already selected,
			// add it to the selected objects vector.
			if (selectedObject && !DetectedObject::contains(app->selectedObjects, selectedObject)) {
				app->logger.writeNormal("Selected object.");
				selectedObject->setSelected(true);
				app->selectedObjects.push_back(selectedObject);
			}
		}
	}
}

void MouseHandler::handleReleased(int x, int y, int button) {
	pressedInsidePlayer = false;
	pressedInsideTimeline = false;
}