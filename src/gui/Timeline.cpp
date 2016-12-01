#include "Timeline.h"
Timeline::Timeline(int x, int y, float w, float h, ofColor color) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
	
	int n = numNotches();
	for (int i = 0; i < n; i++) {
		int x_pos = x + i*(w / n);
		int y_pos = (i % 5 == 0) ? y : y + h/2;
		int width = 1;
		int height = (i % 5 == 0) ? h : h / 2;
		ofRectangle rect = ofRectangle(x_pos, y_pos, width, height);
		notches.push_back(rect);
	}
}

int Timeline::getX() {
	return x;
}

int Timeline::getY() {
	return y;
}

float Timeline::width() {
	return w;
}

float Timeline::height() {
	return h;
}

ofColor Timeline::getColor() {
	return ofColor();
}

void Timeline::draw() {
	// Draw the outer box.
	ofSetColor(color);
	ofFill();
	ofDrawRectangle(x, y, w, h);

	// Draw the notches.
	ofSetColor(255, 255, 255);
	ofNoFill();
	for (ofRectangle notch : notches) {
		ofDrawRectangle(notch);
	}
}

int Timeline::numNotches() {
	return 60;
}
