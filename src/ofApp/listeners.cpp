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
	this->bAnalyze = b;

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
	
	this->analyze();
}

void ofApp::analyze(bool doThreshold) {
	ofPixels frame = timeline->getVideoPixels();

	float w = frame.getWidth();
	float h = frame.getHeight();

	bLearnBackground = true;

	// Computer vision analysis.
	colorImg.setFromPixels(frame);
	grayImage = colorImg;
	threshold = grayImage;
	if (doThreshold) {
		threshold.adaptiveThreshold(this->blockSize);
	}
	contourFinder.findContours(threshold, this->minBlobAreaSlider, this->maxBlobAreaSlider,
		this->nMaxBlobsSlider,
		this->findHolesToggle, false);

	// Update the contours vector in ofApp.
	this->contours = blobsToPolylines(contourFinder.blobs);

	// Log completion. 
	logger.writeNormal("Finished vision analysis.");
}

void ofApp::minBlobAreaSliderChanged(int &area) {
	this->analyze();
}

void ofApp::maxBlobAreaSliderChanged(int &area) {
	this->analyze();
}

void ofApp::nMaxBlobsSliderChanged(int &n) {
	this->analyze();
}

void ofApp::findHolesToggled(bool &b) {
	this->analyze();
}



void ofApp::dilateToggled(bool &b) {
	if (b) {
		this->threshold.dilate();
		this->analyze(false);
	}
}

void ofApp::erodeToggled(bool &b) {
	if (b) {
		this->threshold.erode();
		this->analyze(false);
	}
}

void ofApp::polygonSelectorToggled(bool &b) {
	// Reset the selected area when toggled.
	this->selectedArea.clear();
	this->polygonSelection = b;
}

void ofApp::thresholdBlockSizeChanged(int &blockSize) {
	this->blockSize = blockSize;

	// re-analyze
	this->analyze(); 
}

void ofApp::saveFrame() {
	// Follow schema: frame, centroids..., areas...
	float frame = this->getCurrentFrame();

	vector<ofPoint> centroids;
	vector<float> areas;
	for (ofPolyline p : this->selectedAreas) {
		centroids.push_back(p.getCentroid2D());
		areas.push_back(p.getArea());
	}

	this->output << frame << ",";
	for (ofPoint centroid : centroids) {
		this->output << "[" << centroid.x << "," << centroid.y << "],";
	}

	for (float area : areas) {
		this->output << area << ",";
	}

	this->output << "\n";
	this->selectedAreas.clear();
}