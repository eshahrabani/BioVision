#pragma once
#include "ofMain.h"

class Timeline {
public:
	// Constructor.
	Timeline(int x, int y, float w, float h, const ofColor& color, int numNotches);

	// Getter methods. 
	int getX();
	int getY();
	float width();
	float height();
	const ofColor& getColor();
	int getNumNotches();
	const std::vector<ofRectangle>& getNotches();
	const ofPoint& getPlaySliderPosition();

	// Setter methods.
	void setX(int);
	void setY(int);
	void width(float);
	void height(float);
	void setColor(const ofColor&);
	void setNumNotches(int);
	void setPlaySliderPosition(int, int);

	// Draws the timeline.
	void draw();
private:
	int x, y;
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