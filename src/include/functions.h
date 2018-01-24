/* 
 * FUNCTIONS.H
 * 
 * This file declares state-independent functions to be used throughout
 * the BioVision program. All functions can be treated as black-boxes
 * that do not modify the state of their parameters. 
 */

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h";

/*
Applies a displacement to each point of a single polyline.
*/
ofPolyline displacePolyline(const ofPolyline &polyline, float dx, float dy);

/*
Applies a displacement to each point of every polyline.
*/
vector<ofPolyline> displacePolylines(const vector<ofPolyline> &polylines, float dx, float dy);

/*
 * Draw a polyline using (x,y) as an offset anchor point. 
 *
 * For example (x,y) = (2,3) uses the point (2,3) to offset 
 * every point in the polyline.
 */
void drawPolyline(const ofPolyline& polyline, float x, float y);

/*
 * Draw a vector of polylines that all use (x,y) as an offset anchor point.
 */
void drawPolylines(const vector<ofPolyline>& polylines, float x, float y);

/* Convert a blob to a polyline. */
ofPolyline blobToPolyline(const ofxCvBlob& blob);

/* 
 * Convert a vector of blobs to a vector of polylines.
 *
 * Each blob will become one polyline. 
*/
vector<ofPolyline> blobsToPolylines(const vector<ofxCvBlob>& blobs);