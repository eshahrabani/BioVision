#include "functions.h"
 
ofPolyline displacePolyline(const ofPolyline &polyline, float dx = 0.0, float dy = 0.0) {
	ofPolyline p = ofPolyline();
	for (ofPoint pt : polyline.getVertices()) {
		p.addVertex(ofPoint(pt.x + dx, pt.y + dy));
	}

	return p;
}

vector<ofPolyline> displacePolylines(const vector<ofPolyline> &polylines, float dx = 0.0, float dy = 0.0) {
	vector<ofPolyline> displacedPolylines;
	for (ofPolyline p : polylines) {
		displacedPolylines.push_back(displacePolyline(p, dx, dy));
	}
	return displacedPolylines;
}

void drawPolyline(const ofPolyline& polyline, float x=0.0, float y=0.0) {
	displacePolyline(polyline, x, y).draw();
}

void drawPolylines(const vector<ofPolyline>& polylines, float x = 0.0, float y = 0.0) {
	for (ofPolyline p : polylines) {
		drawPolyline(p, x, y);
	}
}

ofPolyline blobToPolyline(const ofxCvBlob& blob) {
	return(ofPolyline(blob.pts));
}

vector<ofPolyline> blobsToPolylines(const vector<ofxCvBlob>& blobs) {
	vector<ofPolyline> polylines;
	for (ofxCvBlob blob : blobs) {
		polylines.push_back(ofPolyline(blob.pts));
	}
	return polylines;
}

bool polylinesOverlap(ofPolyline p1, ofPolyline p2) {
	// Walk along the bounding box of p1 and see if any of them are in p2.
	ofRectangle boundingBox = p1.getBoundingBox();
	float w = boundingBox.width;
	float h = boundingBox.height;
	float x = boundingBox.x;
	float y = boundingBox.y;

	// Walk along the width.
	for (int ix = x; ix <= x + w; ix++) {
		if (p2.inside(ix, y) || p2.inside(ix, y + h)) {
			return true;
		}
	}

	// Walk along the height;
	for (int iy = y; iy <= y + h; iy++) {
		if (p2.inside(x, iy) || p2.inside(x + w, iy)) {
			return true;
		}
	}

	return false;
}