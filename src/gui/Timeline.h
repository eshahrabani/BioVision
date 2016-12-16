#pragma once
#include "ofMain.h"

class Timeline {
public:
	// Constructor.
	Timeline(float x, float y, float w, float h, const ofColor& color, int numNotches);
	Timeline(float vidX, float vidY, float vidWidth, float vidHeight,
		float tX, float tY, float tWidth, float tHeight,
		const ofColor& tColor, int numNotches);

	// Getter methods. 
	float getTimelineX();
	float getTimelineY();
	float getTimelineWidth();
	float getTimelineHeight();
	const ofColor& getColor();
	int getNumNotches();
	const std::vector<ofRectangle>& getNotches();
	const ofPoint& getPlaySliderPosition();

	// Setter methods.
	void setX(float);
	void setY(float);
	void setTimelineWidth(float);
	void setTimelineHeight(float);
	void setColor(const ofColor&);
	void setNumNotches(int);
	void setPlaySliderPosition(float, float);
	void setPlaySliderX(float);
	void play();
	void pause();
	void load();
	bool isLoaded();
	void update();

	// Draws the timeline.
	void draw();

	// Test if a point is inside the timeline.
	bool isInside(float, float);
private:
	float x, y;
	float w, h;
	ofColor color;
	int numNotches;
	ofVideoPlayer videoPlayer;

	// Vector of the timeline notches.
	std::vector<ofRectangle> notches;
	
	// Play slider indicating video location. 
	ofRectangle playSlider;

	// Methods.
	void populateNotchesVector();
};