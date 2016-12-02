#pragma once
#include "ofMain.h"

class Timeline {
public:
	// Constructor.
	Timeline(float x, float y, float w, float h, const ofColor& color, int numNotches);

	// Getter methods. 
	float getX();
	float getY();
	float width();
	float height();
	const ofColor& getColor();
	int getNumNotches();
	const std::vector<ofRectangle>& getNotches();
	const ofPoint& getPlaySliderPosition();

	// Setter methods.
	void setX(float);
	void setY(float);
	void width(float);
	void height(float);
	void setColor(const ofColor&);
	void setNumNotches(int);
	void setPlaySliderPosition(float, float);

	// Draws the timeline.
	void draw();
private:
	float x, y;
	float w, h;
	ofColor color;
	int numNotches;

	// Vector of the timeline notches.
	std::vector<ofRectangle> notches;
	
	// Play slider indicating video location. 
	ofRectangle playSlider;

	// Methods.
	void populateNotchesVector();
};