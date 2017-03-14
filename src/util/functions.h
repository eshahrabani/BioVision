#pragma once
#include "ofApp.h"

void drawPolyline(ofPolyline polyline, float x, float y);

ofPolyline blobToPolyline(ofxCvBlob blob);

std::vector<ofPolyline> blobsToPolylines(std::vector<ofxCvBlob> blobs);