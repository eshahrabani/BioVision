#pragma once
#include "ofMain.h"

// A wrapper class for ofRectangle, enabling GUI functionality.
class Marquee {

public:

	// Constructors.
	Marquee();
	Marquee(int x, int y, float w, float h);
	~Marquee();

	// Methods. 
	void set(int x, int y, float w, float h);
	void set(const ofRectangle& rect);
	void setFromCenter(int x, int y, float w, float h);
	void setFromDrag(int x_i, int y_i, int x_f, int y_f);

	int getX();
	int getY();
	float width();
	float height();

	bool inside(int x, int y);
	void draw();
	void clear();

private:
	ofRectangle* rect;
};
