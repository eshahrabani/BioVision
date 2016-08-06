#pragma once
#include "ofMain.h"
#include "ofApp.h"
#include <iostream>
using namespace std;

// KeyParser class reads in keys pressed and sends actions to ofApp. 
// It also stores the state of some important keys. 

class ofApp;

class KeyParser {

public:

	// Connects KeyParser to ofApp. 
	KeyParser(ofApp* app);

	// Parses keys and executes commands. 
	void parsePressed(int key);
	void parseReleased(int key);

	bool right_pressed;
	bool left_pressed;
	bool ctrl_pressed;

	ofApp* app;
};