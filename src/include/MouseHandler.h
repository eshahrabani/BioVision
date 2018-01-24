#pragma once

#include <string>
#include <stdlib.h>

// Forward declaration to avoid circular includes. 
class ofApp;

// MouseHandler handles mouse events, sending actions to ofApp.
// It also stores positions of several mouse events. 
class MouseHandler {
public:
	
	// Constructor that connects MouseHandler to ofApp.
	MouseHandler(ofApp* app);

	// Updates current location of mouse when mouse is moved.
	void handleMoved(int x, int y);

	// Executes commands on ofApp when mouse is dragged.
	void handleDragged(int x, int y, int button);

	// Executes commands on ofApp when mouse is pressed.
	void handlePressed(int x, int y, int button);

	// Executes commands on ofApp when mouse is released.
	void handleReleased(int x, int y, int button);

	// Executes commands on ofApp when mouse enters.
	void handleEntered(int x, int y);

	// Executes commands on ofApp when mouse exits. 
	void handleExited(int x, int y);

	// Current mouse position.
	int pos_x;
	int pos_y;

	// Last clicked position.
	int last_clicked_x;
	int last_clicked_y;
	int last_clicked_button; 

	// Bools.
	bool pressedInsidePlayer = false;
	bool pressedInsideTimeline = false;

	// Pointer to ofApp.
	ofApp* app;
};