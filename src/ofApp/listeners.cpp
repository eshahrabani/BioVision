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

void ofApp::createObjectPressed() {
	// At least one full polygon is selected.
	if (this->selectedAreas.size() > 0) {
		for (ofPolyline polygon : this->selectedAreas) {
			this->detectedObjects.push_back(DetectedObject(polygon));
		}
		this->selectedAreas.clear();
		this->polygonSelectorToggle = !this->polygonSelectorToggle;
	}
}

void ofApp::markNewObjectButtonPressed() {
	if (this->selectedObjects.size() == 1) {
		string name = ofSystemTextBoxDialog("Enter the name of the selected object.");
		if (name == "") return;

		this->knownObjectsPanel.addItem(name);

		// Add a copy of the object to the tracked objects vector.
		DetectedObject obj = *this->selectedObjects.at(0);
		DetectedObject copy(obj);
		this->trackedObjects.push_back(copy);
	}
}

void ofApp::markedObjectPressed(string name) {
	cout << name << endl;
}

void ofApp::selectObjectToggled(bool &b) {
	if (b) {
		this->selectObjectToggle.setName("Selecting...");
	}
	else {
		// Unselect all currently selected objects.
		for (DetectedObject* pObj : this->selectedObjects) {
			logger.writeNormal("Unselecting object.");
			pObj->setSelected(false);
		}

		// Clear selected objects vector.
		this->selectedObjects.clear();

		this->selectObjectToggle.setName("Select object(s)");
	}
}

void ofApp::consolidateObjectsPressed() {
	// Consolidate the first two selected objects.
	if (this->selectedObjects.size() == 2) {
		DetectedObject* obj1 = this->selectedObjects.at(0);
		DetectedObject* obj2 = this->selectedObjects.at(1);
		obj1->consolidateWith(*obj2);

		// Find obj2 in detected objects and delete it.
		int obj2Index = DetectedObject::getIndexByAddress(this->detectedObjects, obj2);
		if (obj2Index != -1) {
			this->detectedObjects.erase(this->detectedObjects.begin() + obj2Index);
		}

		// Unselect all objects now.
		this->selectObjectToggle = !this->selectObjectToggle;
	}
	else {
		logger.writeNormal("Select only two objects at a time for consolidation.");
	}
}

void ofApp::separateObjectPressed() {
	logger.writeNormal("Separating objects...");
	// Must select a single polygon area to separate first.
	if (this->selectedAreas.size() == 1) {
		ofPolyline area = this->selectedAreas.at(0);
		
		// Find parts of detected objects inside this area and split them off.
		vector<int> delIndices;
		int idx = 0;
		for (DetectedObject& dtObject : this->detectedObjects) {
			bool partiallyInside = polylinesOverlap(area, dtObject.getPolyline());
			
			// Separate the object.
			if (partiallyInside) {
				logger.writeNormal("Found an object partially inside selected area.");
				vector<ofPoint> newObjectPts;
				vector<ofPoint> oldObjectPts;
				vector<ofPoint> objectVerts = dtObject.getPolyline().getVertices();
				for (int i = 0; i < objectVerts.size(); i++) {
					ofPoint pt = objectVerts.at(i);
					if (area.inside(pt)) {
						newObjectPts.push_back(pt);
					}
					else {
						oldObjectPts.push_back(pt);
					}
				}

				this->detectedObjects.push_back(DetectedObject(ofPolyline(newObjectPts)));
				this->detectedObjects.push_back(DetectedObject(ofPolyline(oldObjectPts)));
				
				this->selectedAreas.clear();
				delIndices.push_back(idx);

				break;
			}
			idx++;
		}
		
		// Delete old objects.
		for (int i : delIndices) {
			detectedObjects.erase(detectedObjects.begin() + i);
		}

		// Turn off polygon selector and object selector.
		this->polygonSelectorToggle = !this->polygonSelectorToggle;
		this->selectObjectToggle = !this->selectObjectToggle;
	}
	else {
		logger.writeNormal("Select one area with the polygon selector tool.");
	}
}

void ofApp::deleteObjectPressed() {
	if (this->selectedObjects.size() >= 1) {
		// Take the first selected object's address.
		DetectedObject* addr = this->selectedObjects.at(0);

		// Find the index of this object in the detected objects vector.
		int objIndex = DetectedObject::getIndexByAddress(this->detectedObjects, addr);

		// Delete the selected object pointer and the detected object itself.
		this->selectedObjects.erase(this->selectedObjects.begin());
		this->detectedObjects.erase(this->detectedObjects.begin() + objIndex);
	}
	else {
		logger.writeNormal("No objects selected.");
	}
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
	frame.resize(vid_width, vid_height);

	float w = frame.getWidth();
	float h = frame.getHeight();
	logger.writeNormal("Width and height of frame: " + std::to_string(w) + "," + std::to_string(h));
	logger.writeNormal("Width and height of video player: " + std::to_string(vid_width) + "," + std::to_string(vid_height));

	bLearnBackground = true;

	// Computer vision analysis.
	colorImg.setFromPixels(frame);
	grayImage = colorImg;

	if (doThreshold) {
		threshold = grayImage;
		threshold.adaptiveThreshold(this->blockSize);
	}

	contourFinder.findContours(threshold, this->minBlobAreaSlider, this->maxBlobAreaSlider,
		this->nMaxBlobsSlider,
		this->findHolesToggle, false);

	this->detectedObjects.clear();
	this->selectedObjects.clear();

	for (ofxCvBlob blob : contourFinder.blobs) {
		ofColor blobColor(255, 0, 0);
		this->detectedObjects.push_back(DetectedObject(blob, blobColor, ofPoint(vid_x + vid_width, vid_y)));
	}

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