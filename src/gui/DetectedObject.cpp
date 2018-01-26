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

void DetectedObject::draw(bool drawBoundingBox) {
	this->draw(anchor.x, anchor.y, drawBoundingBox);
}

void DetectedObject::draw(float x, float y, bool drawBoundingBox) {
	if (drawBoundingBox) {
		ofRectangle box = this->points.getBoundingBox();
		ofSetColor(197, 66, 244);
		ofNoFill();
		ofDrawRectangle(anchor.x + box.x, anchor.y + box.y, box.width, box.height);
	}
	ofSetColor(blobColor);
	drawPolyline(points, x, y)
}

void DetectedObject::setBlobColor(ofColor color) {
	blobColor = color;
}

ofxCvBlob DetectedObject::getBlob() {
	return blob;
}

const ofPolyline DetectedObject::getPoints() {
	return this->points;
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

void DetectedObject::consolidateWith(DetectedObject &other) {
	vector<ofPoint> verts = other.getPoints().getVertices();
	this->points.addVertices(verts);
	this->points.close();
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
