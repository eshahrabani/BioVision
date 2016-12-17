#pragma once
#include "ofMain.h"

class Timeline {
public:
	// Constructor.
	Timeline(float vidX, float vidY, float vidWidth, float vidHeight,
		float tX, float tY, float tWidth, float tHeight,
		const ofColor& tColor, int numNotches);

	// Getter methods. 
	float getTimelineX();
	float getTimelineY();
	float getTimelineWidth();
	float getTimelineHeight();

	float getVidX();
	float getVidY();
	float getVidWidth();
	float getVidHeight();

	const ofColor& getColor();
	int getNumNotches();
	const std::vector<ofRectangle>& getNotches();
	ofPoint getPlaySliderPosition();

	// Setter methods.
	void setTimelineX(float);
	void setTimelineY(float);
	void setTimelineWidth(float);
	void setTimelineHeight(float);

	void setVidX(float);
	void setVidY(float);
	void setVidWidth(float);
	void setVidHeight(float);

	void setTimelineColor(const ofColor&);
	void setNumNotches(int);
	void setPlaySliderPosition(float, float);
	void setPlaySliderX(float);
	
	// Video utilities.
	void load();
	bool isVideoLoaded();
	bool isVideoPlaying();
	ofPixels getVideoPixels();

	// Video controls.
	void play();
	void pause();
	void nextFrame();
	void previousFrame();
	void setVideoSpeed(float);
	void restartVideo();
	
	// Updates the timeline.
	void update();

	// Draws the timeline.
	void draw();

	// Test if a point is inside the timeline.
	bool isInsideTimeline(float, float);
private:

	// Dimensions.
	float tX, tY;
	float tWidth, tHeight;
	float vidX, vidY;
	float vidWidth, vidHeight;

	// Objects.
	ofColor timelineColor;
	int numNotches;
	ofVideoPlayer videoPlayer;
	std::vector<ofRectangle> notches;
	ofRectangle playSlider;

	// Methods.
	void populateNotchesVector();
};