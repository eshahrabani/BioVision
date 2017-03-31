#include "functions.h"
 
void drawPolyline(const ofPolyline& polyline, float x=0.0, float y=0.0) {
	ofPolyline p = ofPolyline();

	// Perform the offset on a new polyline. 
	for (ofPoint pt : polyline.getVertices()) {
		p.addVertex(ofPoint(pt.x + x, pt.y + y));
	}
	p.draw();
}

void drawPolylines(const vector<ofPolyline>& polylines, float x = 0.0, float y = 0.0) {
	for (ofPolyline p : polylines) {
		p.draw();
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