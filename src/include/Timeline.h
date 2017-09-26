// Timeline class for the app. This class contains the video player
// and encapsulates all of the methods of the player.
//
// Important note: calling functions of the player within this class
// that affects state of the video player (e.g. play) makes it difficult
// for ofApp to keep track of state (for GUI). Therefore, use ofApp to call
// methods such as play() and pause(). In sum, the flow of control
// should always be ofApp -> Timeline -> video player, with no bidirectional
// communication. 

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

	int getCurrentFrame();

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
	void setFrame(int);
	void setFrameFromMouseX(float);
	void setVideoSpeed(float);
	void restartVideo();
	
	// Updates the timeline.
	void updatePlaySlider();
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