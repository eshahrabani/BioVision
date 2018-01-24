#include "DetectedObject.h";

DetectedObject::DetectedObject(ofxCvBlob blob, ofColor blobColor, ofPoint anchor) {
	this->blob = blob;
	this->points = ofPolyline(blob.pts);
	this->points.close();

	setBlobColor(blobColor);
	setAnchor(anchor);

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

ofPoint DetectedObject::getClosestPoint(ofPoint target, bool useAnchor) {
	if (useAnchor) {
		ofPolyline adjusted = displacePolyline(this->points, anchor.x, anchor.y);
		return adjusted.getClosestPoint(target);
	}
	else {
		return this->points.getClosestPoint(target);
	}
}

bool DetectedObject::containsPoint(ofPoint pt, bool useAnchor) {
	// Adjust internal polyline based on the anchor.
	if (useAnchor) {
		ofPolyline adjustedPolyline = displacePolyline(this->points, anchor.x, anchor.y);
		return adjustedPolyline.inside(pt);
	}
	else {
		return this->points.inside(pt);
	}
}
