#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor blobColor = ofColor(255, 0, 0), ofPoint anchor=ofPoint(0, 0));

	void update();

	void draw(bool drawBoundingBox=true);
	void draw(float x, float y, bool drawBoundingBox=true);

	void setBlobColor(ofColor color);
	void setAnchor(ofPoint anchor);

	ofxCvBlob getBlob();
	const ofPolyline getPoints();

	ofPoint getClosestPoint(ofPoint target, bool useAnchor=true);

	/*
	 * Add the points of the other object to this object. 
	 */
	void consolidateWith(DetectedObject &other); 

	bool containsPoint(ofPoint pt, bool useAnchor=true);

private:
	ofxCvBlob blob;
	ofPolyline points;

	ofColor blobColor;
	ofPoint anchor;
};