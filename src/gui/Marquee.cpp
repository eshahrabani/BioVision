#pragma once
#include "Marquee.h"

Marquee::Marquee() : Marquee(0, 0, 0, 0) {}

Marquee::Marquee(int x, int y, float w, float h) {
	rect = new ofRectangle(x, y, w, h);
}

Marquee::~Marquee() {
	delete rect;
}

// Sets a marquee with (x,y) as the top left corner.
void Marquee::set(int x, int y, float w, float h) {

	// Resize the rectangle's dimensions.
	rect->set(x, y, w, h);
}

// Sets a marquee with (x,y) as the center.
void Marquee::setFromCenter(int x, int y, float w, float h) {
	rect->setFromCenter(x, y, w, h);
}

void Marquee::setFromDrag(int x_i, int y_i, int x_f, int y_f) {

	// Assuming 45 degree angles (square marquee): w = h = (d/2)*sqrt(2)
	float d = sqrt(pow(x_f - x_i, 2) + pow(y_f - y_i, 2));	// Apply distance formula.
	int w, h;
	w = h = (d / 2)*sqrt(2);

	this->set(x_i, y_i, w, h);
}

int Marquee::getX() {
	return rect->getX();
}

int Marquee::getY() {
	return rect->getY();
}

float Marquee::width() {
	return rect->getWidth();
}

float Marquee::height() {
	return rect->getHeight();
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
