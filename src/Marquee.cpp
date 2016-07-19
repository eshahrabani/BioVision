#include "Marquee.h"

void Marquee::set(int x, int y, int w, int h) {

	// If a rectangle already exists, just resize it.
	if (rect != nullptr) {
		rect->set(x, y, w, h);
	}
	// Otherwise, create a new rectangle.
	else {
		rect = new ofRectangle(x, y, w, h);
	}
}

void Marquee::setFromCenter(int x, int y, int w, int h) {
	if (rect != nullptr) {
		rect->set(x, y, w, h);
	}
	else {
		rect = new ofRectangle(x, y, w, h);
	}
}

void Marquee::draw() {
	if (rect != nullptr) {
		ofNoFill();
		ofDrawRectangle(*rect);
		ofFill();
	}

	else {
		ofDrawRectangle(0, 0, 0, 0);
	}
}

void Marquee::clear() {
	delete rect;
	rect = nullptr;
}
