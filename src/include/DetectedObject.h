#pragma once

#include "ofMain.h";
#include "ofxOpenCv.h";
#include "functions.h";

class DetectedObject {
public:
	DetectedObject(ofxCvBlob blob, ofColor objColor = ofColor(255, 0, 0), ofPoint anchor=ofPoint(0, 0));
	DetectedObject(ofPolyline polyLine, ofColor objColor = ofColor(255, 0, 0), ofPoint anchor = ofPoint(0, 0));
	DetectedObject(ofPolyline polyline, int videoFrame, ofPixels videoPixels, ofColor objColor = ofColor(255, 0, 0), ofPoint anchor = ofPoint(0, 0));
	DetectedObject(const DetectedObject& other);

	void update();

	void draw(bool drawBoundingBox=true, bool fillBoundingBox=false);

	void setObjectColor(ofColor color);
	void setPoints(ofPolyline points);

	const ofColor getOutlineColor() const;
	const ofPolyline getPolyline() const;
	const ofPixels getVideoPixels() const;

	int getFrame();
	ofPoint getClosestPoint(ofPoint target);
	ofColor getVideoObjectAverageColor();
	ofPoint getVideoObjectCentroid();
	float getVideoObjectArea();

	void setSelected(bool s);

	/*
	 * Add the points of the other object to this object. 
	 */
	void consolidateWith(DetectedObject &other); 

	bool containsPoint(ofPoint pt);

	ofColor selectedColor;

	// Returns the index of the object in the vector.
	// If not found, returns -1.
	static int getIndexByAddress(vector<DetectedObject> &v, DetectedObject* addr);
	static bool contains(vector<DetectedObject>& v, DetectedObject& obj);
	static bool contains(vector<DetectedObject*> pVec, DetectedObject* addr);

private:
	ofPolyline points;
	ofPoint anchor;
	ofPixels videoPixels;
	int videoFrame;
	ofColor objectColor;
	ofColor boundingBoxColor;

	bool selected;
};