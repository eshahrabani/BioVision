#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor blobColor = ofColor(255, 0, 0), ofPoint anchor=ofPoint(0, 0));

	void update();

	void draw(bool drawBoundingBox=true, bool fillBoundingBox=false);
	void draw(float x, float y, bool drawBoundingBox=true, bool fillBoundingBox=false);

	void setBlobColor(ofColor color);
	void setAnchor(ofPoint anchor);

	ofxCvBlob getBlob();
	const ofPolyline getPolyline();

	ofPoint getClosestPoint(ofPoint target, bool useAnchor=true);

	void setSelected(bool s);

	/*
	 * Add the points of the other object to this object. 
	 */
	void consolidateWith(DetectedObject &other); 

	bool containsPoint(ofPoint pt, bool useAnchor=true);

	ofColor selectedColor;

	// Returns the index of the object in the vector.
	// If not found, returns -1.
	static int getIndexByAddress(vector<DetectedObject> &v, DetectedObject* addr);
	static bool contains(vector<DetectedObject>& v, DetectedObject& obj);
	static bool contains(vector<DetectedObject*> pVec, DetectedObject* addr);

private:
	ofxCvBlob blob;
	ofPolyline points;

	ofColor blobColor;
	ofColor boundingBoxColor;
	ofPoint anchor;

	bool selected;
};