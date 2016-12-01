#pragma once
#include "ofMain.h"

class Timeline {
public:
	// Constructor.
	Timeline(int x, int y, float w, float h, ofColor color);

	// Read-only methods.
	int getX();
	int getY();
	float width();
	float height();
	ofColor getColor();

	// Void methods.
	void draw();
private:
	int x, y;
	float w, h;
	ofColor color;

	// Vector of the timeline notches.
	std::vector<ofRectangle> notches;

	// Methods.
	int numNotches();
};