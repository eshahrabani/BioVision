#pragma once
#include <iostream>
#include "ofMain.h"
#include "ofxGui.h";

using std::vector;

class KnownObjectsPanel : public ofxPanel {
public:
	KnownObjectsPanel();

	void addItem(string name);
	void removeItem(string name);
	void clearItems();

	bool mousePressed(ofMouseEventArgs& args);
};