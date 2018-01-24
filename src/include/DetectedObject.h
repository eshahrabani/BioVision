#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor blobColor = ofColor(255, 0, 0), ofPoint anchor=ofPoint(0, 0));

	void update();

	void draw();
	void draw(float x, float y);

	void setBlobColor(ofColor color);
	void setAnchor(ofPoint anchor);

	ofxCvBlob getBlob();
	ofPoint getClosestPoint(ofPoint target, bool useAnchor=true);

	bool containsPoint(ofPoint pt, bool useAnchor=true);

private:
	ofxCvBlob blob;
	ofPolyline points;

	ofColor blobColor;
	ofPoint anchor;
};