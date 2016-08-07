#pragma once
#include <iostream>
using namespace std;
 
// Forward declaration of ofApp to avoid circular includes, since ofApp.h includes this file. 
class ofApp;

// KeyHandler handles keys pressed, sending actions to ofApp. 
// It also stores the current state of CTRL, RIGHT, and LEFT keys.
class KeyHandler {

public:

	// Constructor that connects KeyHandler to ofApp. 
	KeyHandler(ofApp* app);

	// Parses pressed keys and executes relevant commands on ofApp. 
	void handlePressed(int key);

	// Parses released keys to update key states. 
	void handleReleased(int key);

	// Bools for storing key states.
	bool right_pressed;
	bool left_pressed;
	bool ctrl_pressed;
	bool alt_pressed;

	// Pointer to ofApp. 
	ofApp* app;
};