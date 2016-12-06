#include "Timeline.h"
Timeline::Timeline(float x, float y, float w, float h, const ofColor& color, int numNotches) {
	setX(x);
	setY(y);
	width(w);
	height(h);
	setColor(color);
	setNumNotches(numNotches);
	playSlider.set(x, y, 1, h);
}

float Timeline::getX() {
	return x;
}

float Timeline::getY() {
	return y;
}

float Timeline::width() {
	return w;
}

float Timeline::height() {
	return h;
}

const ofColor& Timeline::getColor() {
	return color;
}

int Timeline::getNumNotches() {
	return numNotches;
}

const std::vector<ofRectangle>& Timeline::getNotches() {
	return notches;
}

const ofPoint& Timeline::getPlaySliderPosition() {
	return ofPoint(playSlider.getX(), playSlider.getY());
}

void Timeline::setX(float x) {
	this->x = x;
}

void Timeline::setY(float y) {
	this->y = y;
}

void Timeline::width(float w) {
	this->w = w;
}

void Timeline::height(float h) {
	this->h = h;
}

void Timeline::setColor(const ofColor& color) {
	this->color = color;
}

void Timeline::setNumNotches(int n) {
	this->numNotches = n;
}

void Timeline::setPlaySliderPosition(float x, float y) {
	playSlider.set(x, y, 1, h);
}

void Timeline::setPlaySliderX(float x) {
	// Check if x is inside the timeline.
	if (x < this->x || x > this->x + w) {
		return;
	}

	float origY = playSlider.y;
	playSlider.set(x, origY, 1, h);
}

void Timeline::draw() {
	// Draw the outer box.
	ofSetColor(color);
	ofFill();
	ofDrawRectangle(x, y, w, h);

	// Check if notches vector is fully populated.
	// If not, populate it with rectangles. 
	if (notches.size() != numNotches) {
		populateNotchesVector();
	}

	// Draw the notches.
	ofSetColor(255, 255, 255);
	ofNoFill();
	for (ofRectangle notch : notches) {
		ofDrawRectangle(notch);
	}

	// Draw the play slider.
	ofSetColor(50, 255, 61);
	ofNoFill();
	ofDrawRectangle(playSlider);
}

bool Timeline::isInside(float x, float y) {
	ofRectangle rect = ofRectangle(this->x, this->y, w, h);
	return rect.inside(x, y);
}

void Timeline::populateNotchesVector() {
	for (int i = 0; i <= numNotches; i++) {
		int x_pos = x + i*(w / numNotches);
		int y_pos = (i % 5 == 0) ? y : y + h / 2;
		int width = 1;
		int height = (i % 5 == 0) ? h : h / 2;
		ofRectangle rect = ofRectangle(x_pos, y_pos, width, height);
		notches.push_back(rect);
	}
}

