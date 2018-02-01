#include "DetectedObject.h";

DetectedObject::DetectedObject(
	ofxCvBlob blob, ofColor blobColor, ofPoint anchor
) : DetectedObject(ofPolyline(blob.pts), blobColor, anchor) {}

DetectedObject::DetectedObject(ofPolyline polyline, ofColor blobColor, ofPoint anchor) {
	this->points = displacePolyline(polyline, anchor.x, anchor.y);
	if (!this->points.isClosed()) {
		this->points.close();
	}

	this->boundingBoxColor = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));

	setObjectColor(blobColor);
	setSelected(false);
	selectedColor = ofColor(0, 204, 204);
}

void DetectedObject::update() {
}

void DetectedObject::draw(bool drawBoundingBox, bool fillBoundingBox) {
	if (drawBoundingBox) {
		ofRectangle box = this->points.getBoundingBox();
		
		if (this->selected) {
			ofSetColor(objectColor);
		}
		else {
			ofSetColor(this->boundingBoxColor);
		}
		if (fillBoundingBox) {
			ofFill();
		}
		ofDrawRectangle(box.x, box.y, box.width, box.height);
		ofNoFill();
	}

	if (this->selected) {
		ofSetColor(this->selectedColor);
	}
	else {
		ofSetColor(objectColor);
	}
	drawPolyline(this->points, 0, 0);
}

void DetectedObject::setObjectColor(ofColor color) {
	objectColor = color;
}

const ofPolyline DetectedObject::getPolyline() {
	return this->points;
}

ofPoint DetectedObject::getClosestPoint(ofPoint target) {
	return this->points.getClosestPoint(target);
}

void DetectedObject::setSelected(bool s) {
	this->selected = s;
}

void DetectedObject::consolidateWith(DetectedObject &other) {
	vector<ofPoint> verts = other.getPolyline().getVertices();
	this->points.addVertices(verts);
	this->points.close();
}

bool DetectedObject::containsPoint(ofPoint pt) {
	return this->points.inside(pt);
}

int DetectedObject::getIndexByAddress(vector<DetectedObject> &objects, DetectedObject* addr) {
	int index = -1;
	for (int i = 0; i < objects.size(); i++) {
		if (&objects.at(i) == addr) {
			index = i;
			break;
		}
	}
	 
	return index;
}

bool DetectedObject::contains(vector<DetectedObject>& v, DetectedObject& obj) {
	return getIndexByAddress(v, &obj) != -1;
}

bool DetectedObject::contains(vector<DetectedObject*> pVec, DetectedObject * addr) {
	bool contains = false;

	for (DetectedObject* pObj : pVec) {
		if (pObj == addr) {
			contains = true;
			break;
		}
	}

	return contains;
}
