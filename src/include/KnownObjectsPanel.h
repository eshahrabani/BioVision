#pragma once
#include <iostream>
#include "ofMain.h"
#include "ofxGui.h";

using std::vector;

class KnownObjectsPanel : public ofxPanel {
public:
	KnownObjectsPanel();
	~KnownObjectsPanel();

	bool mousePressed(ofMouseEventArgs& args);

	void addItem(string name);
	void clearItems();

	void itemPressed(string name);

private:
	vector<ofxButton*> pButtons;
};