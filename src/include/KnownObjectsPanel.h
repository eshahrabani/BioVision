#pragma once
#include "ofMain.h";

class KnownObjectsPanel {
public:
	KnownObjectsPanel(float x = 0, float y = 0, float width = 0, float height = 0);
	~KnownObjectsPanel();

	void draw();
	void draw(float x, float y);

	void mousePressed(ofMouseEventArgs& args);

	void setDimensions(float width = 0, float height = 0);
	void setPosition(float x = 0, float y = 0);

	void setup(float x, float y, float width, float height);
private:
	float x;
	float y;
	
	float width;
	float height;
};