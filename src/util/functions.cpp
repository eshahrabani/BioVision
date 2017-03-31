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