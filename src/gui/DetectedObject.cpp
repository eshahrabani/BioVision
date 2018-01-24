#include "DetectedObject.h";

DetectedObject::DetectedObject(ofxCvBlob blob, ofColor blobColor) {
	this->blob = blob;
	this->points = ofPolyline(blob.pts);

	setBlobColor(blobColor);
}

void DetectedObject::update() {
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
