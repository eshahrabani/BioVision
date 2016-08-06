#pragma once
#include "ofMain.h"

// A wrapper class for ofRectangle, enabling GUI functionality.
class Marquee {
public:

	// Constructors.
	Marquee();
	Marquee(int x, int y, int w, int h);
	~Marquee();

	// Methods. 
	void set(int x, int y, int w, int h);
	void set(const ofRectangle& rect);
	void setFromCenter(int x, int y, int w, int h);
	bool inside(int x, int y);
	void draw();
	void clear();
private:

	// Fields. 
	ofRectangle* rect;
};
