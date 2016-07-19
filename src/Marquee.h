#pragma once
#include "ofMain.h"

class Marquee {
public:
	void set(int x, int y, int w, int h);
	void setFromCenter(int x, int y, int w, int h);
	void draw();
	void clear();
private:
	ofRectangle* rect = nullptr;
};
