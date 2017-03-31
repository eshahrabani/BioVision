#include "ofApp.h"

void ofApp::load() {
	logger.writeVerbose("From ofApp: calling load() on timeline.");
	timeline->load();
}


// This method is called when the state of the play toggle is changed,
// either graphically or via code (play_toggle = !play_toggle).  
void ofApp::play_toggled(bool &play) {
	logger.writeVerbose("Play has been toggled.");
	if (timeline->isVideoLoaded()) {
		if (play) {
			// If the play toggle is enabled, play the video 
			// and change the toggle name to "Playing".
			this->play();
			play_toggle.setName("Playing");
			logger.writeNormal("Playing video.");
		}
		else {
			// If the play toggle is disabled, pause the video 
			// and change the toggle name to "Play".
			this->pause();
			play_toggle.setName("Play");
			logger.writeNormal("Pausing video.");
		}
	}
	else {
		// File has not been loaded.
		if (play) {
			// If the play toggle is currently on, turn it back off.
			logger.writeNormal("Load a video before playing.");

			// Turns off the play toggle without recursively triggering 
			// the containing method (play_toggled).
			play_toggle.setWithoutEventNotifications(false);
		}
	}
}

void ofApp::play_speed_changed(float &f) {
	logger.writeVerbose("Setting new play speed from ofApp.");
	timeline->setVideoSpeed(f);
}

// TODO: needs encapsulation of analysis into 
// analyzer object. 
void ofApp::analyze_toggled(bool &b) {
	logger.writeVerbose("Analyze toggled.");

	// If video isn't loaded, exit this method after reverting the toggle 
	// (if it's on). 
	if (!timeline->isVideoLoaded()) {
		if (b)
			analyze_toggle = !analyze_toggle;
		return;
	}

	// If toggle is on, change the analyze toggle name to "analyzing"
	// and pause the video if it's currently playing. 
	if (b) {
		analyze_toggle.setName("Analyzing");
		logger.writeNormal("Performing computer vision analysis.");
		if (play_toggle)
			timeline->pause();
	}
	else {
		analyze_toggle.setName("Analyze");

		// Don't perform any analysis if toggled off. 
		return;
	}

	float w = vid_width;
	float h = vid_height;

	bLearnBackground = true;
	colorImg.allocate(w, h);
	grayImage.allocate(w, h);
	grayBg.allocate(w, h);
	grayDiff.allocate(w, h);
	threshold.allocate(w, h);

	// Computer vision analysis.
	colorImg.setFromPixels(timeline->getVideoPixels());
	colorImg.setROI(0, 0, w, h);
	grayImage.setROI(0, 0, w, h);
	threshold.setROI(0, 0, w, h);
	grayImage = colorImg;
	threshold = grayImage;
	threshold.threshold(100);
	contourFinder.findContours(threshold, 5, vid_width * vid_height, 10,
		false, false);

	// Update the contours vector in ofApp.
	this->contours = blobsToPolylines(contourFinder.blobs);

	// Log completion. 
	logger.writeNormal("Finished vision analysis.");
}