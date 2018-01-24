#include "DetectedObject.h";

DetectedObject::DetectedObject(ofxCvBlob blob, ofColor blobColor, ofPoint anchor) {
	this->blob = blob;
	this->points = ofPolyline(blob.pts);

	setBlobColor(blobColor);
	setAnchor(anchor);
}

DetectedObject::~DetectedObject() {

}

void DetectedObject::update() {
}

void DetectedObject::draw() {
	this->draw(anchor.x, anchor.y);
}

void DetectedObject::draw(float x, float y) {
	ofSetColor(blobColor);
	drawPolyline(points, x, y);
}

void DetectedObject::setBlobColor(ofColor color) {
	blobColor = color;
}

ofxCvBlob DetectedObject::getBlob() {
	return blob;
}


void DetectedObject::setAnchor(ofPoint anchor) {
	this->anchor = anchor;
}
