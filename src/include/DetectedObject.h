#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor blobColor = ofColor(255, 0, 0));

	void update();
	void draw(float x = 0.0, float y = 0.0);

	void setBlobColor(ofColor color);

	ofxCvBlob getBlob();

private:
	ofxCvBlob blob;
	ofPolyline points;

	ofColor blobColor;
};