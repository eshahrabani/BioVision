#pragma once
#include <iostream>
#include "ofMain.h"
#include "ofxGui.h";

using std::vector;

class KnownObjectsPanel : public ofxPanel {
public:
	KnownObjectsPanel();
	~KnownObjectsPanel();

	void addItem(string name);
	void clearItems();

	bool mousePressed(ofMouseEventArgs& args);

private:
	vector<ofxButton*> pButtons;
};