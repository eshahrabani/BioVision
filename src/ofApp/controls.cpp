#include "ofApp.h"

void ofApp::play() {
	logger.writeVerbose("Playing the video.");

	// Turn the play toggle on without triggering play_toggled.
	play_toggle.setWithoutEventNotifications(true);
	timeline->play();
}

void ofApp::pause() {
	logger.writeVerbose("Pausing the video.");

	// Turn the play toggle off without triggering play_toggled.
	play_toggle.setWithoutEventNotifications(false);
	timeline->pause();

	if (this->bAnalyze) {
		this->analyze();
	}
}

void ofApp::next_frame() {
	if (timeline->isVideoPlaying()) {
		logger.writeVerbose(
			"Video is playing; pausing it before jumping to next frame."
		);
		pause();
	}
	logger.writeVerbose("Jumping to next frame.");
	timeline->nextFrame();

	if (this->bAnalyze) {
		this->analyze();
	}
}

void ofApp::previous_frame() {
	if (timeline->isVideoPlaying()) {
		pause();
	}
	timeline->previousFrame();

	if (this->bAnalyze) {
		this->analyze();
	}
}

bool ofApp::isVideoLoaded() {
	return timeline->isVideoLoaded();
}

bool ofApp::isVideoPlaying() {
	return timeline->isVideoPlaying();
}

void ofApp::setFrame(int f) {
	logger.writeVerbose("Setting new frame from ofApp.");
	timeline->setFrame(f);
	
	if (this->bAnalyze) {
		this->analyze();
	}
}

int ofApp::getCurrentFrame()
{
	return timeline->getCurrentFrame();
}

void ofApp::setFrameFromMouseX(float x) {
	logger.writeVerbose("Setting new frame from ofApp using mouse X.");
	timeline->setFrameFromMouseX(x);
	timeline->update();

	if (this->bAnalyze) {
		this->analyze();
	}
}

void ofApp::restartVideo() {
	logger.writeVerbose("Restarting ofApp.");
	timeline->restartVideo();
}