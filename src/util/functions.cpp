#include "functions.h"

// Draws a polyline with anchor point (x,y) representing the top left corner. 
void drawPolyline(ofPolyline polyline, float x=0.0, float y=0.0) {
	// Add x,y to each point in the polyline.
	// This unfortunately needs to be done assuming deep copies of everything are returned,
	// since OF likes to insist on immutability. 
	ofPolyline p = ofPolyline();
	for (ofPoint pt : polyline.getVertices()) {
		p.addVertex(ofPoint(pt.x + x, pt.y + y));
	}
	p.draw();
}

ofPolyline blobToPolyline(ofxCvBlob blob) {
	return(ofPolyline(blob.pts));
}

std::vector<ofPolyline> blobsToPolylines(std::vector<ofxCvBlob> blobs) {
	std::vector<ofPolyline> polylines;
	for (ofxCvBlob blob : blobs) {
		polylines.push_back(blobToPolyline(blob));
	}
	return polylines;
}