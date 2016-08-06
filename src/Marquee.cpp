#pragma once
#include "Marquee.h"

Marquee::Marquee() : Marquee(0, 0, 0, 0) {}

Marquee::Marquee(int x, int y, int w, int h) {
	rect = new ofRectangle(x, y, w, h);
}

Marquee::~Marquee() {
	delete rect;
}

// Sets a marquee with (x,y) as the top left corner.
void Marquee::set(int x, int y, int w, int h) {

	// Resize the rectangle's dimensions.
	rect->set(x, y, w, h);
}

// Sets a marquee with (x,y) as the center.
void Marquee::setFromCenter(int x, int y, int w, int h) {
	rect->setFromCenter(x, y, w, h);
}

// Returns true/false if (x,y) is inside/outside the marquee.
bool Marquee::inside(int x, int y) {
	return rect->inside(x, y);
}

// Sets a marquee using a pre-defined rectangle. 
void Marquee::set(const ofRectangle& rect) {

	// Resize marquee with parameter's values.
	this->set(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

// Draws the marquee.
void Marquee::draw() {
	if (ofGetFill() == OF_FILLED) {
		ofNoFill();
		ofDrawRectangle(*rect);
		ofFill();						// Revert to initial fill state. 
	}
	else {
		ofDrawRectangle(*rect);
	}
}

// Clears the marquee. 
void Marquee::clear() {
	this->set(0, 0, 0, 0);
}
