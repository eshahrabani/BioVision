#include "Timeline.h"
Timeline::Timeline(int x, int y, float w, float h, ofColor color) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
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
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}
