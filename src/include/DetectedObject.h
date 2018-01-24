#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor blobColor = ofColor(255, 0, 0), ofPoint anchor=ofPoint(0, 0));
	~DetectedObject();

	void update();

	void draw();
	void draw(float x, float y);

	// For adding a listener to mouse click on this object.
	// The callback function should accept a pointer to this.
	void onMouseClick(void (*callback)(DetectedObject* pThis));

	// The function called when the mouse is clicked.
	void mouseClicked(float x, float y);

	void setBlobColor(ofColor color);
	void setAnchor(ofPoint anchor);

	ofxCvBlob getBlob();

private:
	ofxCvBlob blob;
	ofPolyline points;

	ofColor blobColor;
	ofPoint anchor;
};