#include "Timeline.h"

Timeline::Timeline(float vidX, float vidY, float vidWidth, float vidHeight, 
	float tX, float tY, float tWidth, float tHeight, 
	const ofColor& tColor, int numNotches) 
{
	setVidX(vidX);
	setVidY(vidY);
	setVidWidth(vidWidth);
	setVidHeight(vidHeight);

	setTimelineX(tX);
	setTimelineY(tY);
	setTimelineWidth(tWidth);
	setTimelineHeight(tHeight);
	
	setTimelineColor(tColor);
	setNumNotches(numNotches);

	// Initialize the play slider.
	setPlaySliderPosition(tX, tY);
}

float Timeline::getTimelineX() {
	return tX;
}

float Timeline::getTimelineY() {
	return tY;
}

float Timeline::getTimelineWidth() {
	return tWidth;
}

float Timeline::getTimelineHeight() {
	return tHeight;
}

float Timeline::getVidX() {
	return vidX;
}

float Timeline::getVidY() {
	return vidY;
}

float Timeline::getVidWidth() {
	return vidWidth;
}

float Timeline::getVidHeight() {
	return vidHeight;
}

const ofColor& Timeline::getColor() {
	return timelineColor;
}

int Timeline::getNumNotches() {
	return numNotches;
}

const std::vector<ofRectangle>& Timeline::getNotches() {
	return notches;
}

ofPoint Timeline::getPlaySliderPosition() {
	return ofPoint(playSlider.getX(), playSlider.getY());
}

void Timeline::setTimelineX(float x) {
	this->tX = x;
}

void Timeline::setTimelineY(float y) {
	this->tY = y;
}

void Timeline::setTimelineWidth(float w) {
	this->tWidth = w;
}

void Timeline::setTimelineHeight(float h) {
	this->tHeight = h;
}

void Timeline::setVidX(float x) {
	vidX = x;
}

void Timeline::setVidY(float y) {
	vidY = y;
}

void Timeline::setVidWidth(float w) {
	vidWidth = w;
}

void Timeline::setVidHeight(float h) {
	vidHeight = h;
}

void Timeline::setTimelineColor(const ofColor& color) {
	this->timelineColor = color;
}

void Timeline::setNumNotches(int n) {
	this->numNotches = n;
}

void Timeline::setPlaySliderPosition(float x, float y) {
	playSlider.set(x, y, 1, tHeight);
}

void Timeline::setPlaySliderX(float x) {
	// Check if x is inside the timeline.
	if (x < this->tX || x > this->tX + tWidth) {
		return;
	}

	float origY = playSlider.y;
	setPlaySliderPosition(x, origY);
}

void Timeline::load() {
	// Open load dialog.
	ofFileDialogResult result = ofSystemLoadDialog();
	cout << "Attempting to load file: " << result.filePath << endl << endl;

	// Attempt to load the file. Will refuse to load if the file extension
	// is invalid, and notifies the user in the console. 
	videoPlayer.loadMovie(result.filePath);

	// Check successful load.
	if (videoPlayer.isLoaded()) {
		cout << "File loaded successfully.\n\n";
	}
	else
		return;

	// Unreachable if the video did not load properly. 
	// Displays the first frame.
	videoPlayer.setPaused(true);
}

bool Timeline::isVideoLoaded() {
	return videoPlayer.isLoaded();
}

bool Timeline::isVideoPlaying() {
	return videoPlayer.isPlaying();
}

ofPixels Timeline::getVideoPixels() {
	return videoPlayer.getPixels();
}

void Timeline::play() {
	if (videoPlayer.isLoaded() && videoPlayer.isPaused()) {
		videoPlayer.setPaused(false);
	}
}

void Timeline::pause() {
	if (videoPlayer.isLoaded() && videoPlayer.isPlaying()) {
		videoPlayer.setPaused(true);
	}
}

void Timeline::nextFrame() {
	if (!videoPlayer.isLoaded()) {
		return;
	}

	// Make sure video is paused.
	pause();

	// Go forward one frame if we are not at the end of the video.
	if (videoPlayer.getCurrentFrame() < videoPlayer.getTotalNumFrames()) {
		videoPlayer.nextFrame();
	}
}

void Timeline::previousFrame() {
	if (!videoPlayer.isLoaded()) {
		return;
	}

	// Make sure video is paused.
	pause();

	// Go backward one frame if we are not at the beginning of the video.
	if (videoPlayer.getCurrentFrame() > 1) {
		videoPlayer.previousFrame();
	}
}

void Timeline::setVideoSpeed(float f) {
	if (!videoPlayer.isLoaded()) {
		return;
	}
	videoPlayer.setSpeed(f);
}

void Timeline::restartVideo() {
	if (!videoPlayer.isLoaded()) {
		return;
	}
	videoPlayer.firstFrame();
	play();
}

// The update method must always be called right before 
// calling the draw method. Otherwise, bugs will occur. 
void Timeline::update() {

	// Make sure the notches vector is populated.
	if (notches.size() != numNotches) {
		populateNotchesVector();
	}

	// No need to run any code below unless the video is loaded.
	if (!videoPlayer.isLoaded()) {
		return;
	}

	// Update the frames of the video player.
	videoPlayer.update();

	// Update the position of the play slider.
	//
	// Calculate percentage complete via the current
	// and total frames. 
	//
	// Use this percentage to find out the current time
	// position of the video. Take the modulo of this
	// time with the number of notches (each representing 1 second),
	// to find out the "effective" current time within the timeline
	// given the number of notches.

	// Finally, the ratio of the effective current time
	// to the number of notches can be used to find
	// the x-pixel position of the slider since we
	// know the width of the timeline. 
	int currentFrame = videoPlayer.getCurrentFrame();
	if (currentFrame == 0) return;

	int nFrames = videoPlayer.getTotalNumFrames();
	float duration = videoPlayer.getDuration();

	float currentTime = ((float)currentFrame / (float)nFrames) * duration;
	currentTime = fmod(currentTime, numNotches); 
	float newX = tX + (currentTime / numNotches) * tWidth;
	setPlaySliderX(newX);

	// For debugging.
	/* 
	cout << "currentFrame: " << currentFrame << endl;
	cout << "nFrames: " << nFrames << endl;
	cout << "duration: " << duration << endl;
	cout << "currentTime: " << currentTime << endl;
	cout << "newX: " << newX << endl;
	cout << "play slider coords: " << getPlaySliderPosition() << endl;
	*/
}

// Must only be called after invoking the update method. 
void Timeline::draw() {
	// Draw the video player.
	videoPlayer.draw(vidX, vidY, vidWidth, vidHeight);

	// Draw the outer box.
	ofSetColor(timelineColor);
	ofFill();
	ofDrawRectangle(tX, tY, tWidth, tHeight);

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

bool Timeline::isInsideTimeline(float x, float y) {
	ofRectangle rect = ofRectangle(tX, tY, tWidth, tHeight);
	return rect.inside(x, y);
}

void Timeline::populateNotchesVector() {
	notches.clear();
	for (int i = 0; i <= numNotches; i++) {
		int x_pos = tX + i*(tWidth / numNotches);
		int y_pos = (i % 5 == 0) ? tY : tY + tHeight / 2;
		int width = 1;
		int height = (i % 5 == 0) ? tHeight : tHeight / 2;
		ofRectangle rect = ofRectangle(x_pos, y_pos, width, height);
		notches.push_back(rect);
	}
}

