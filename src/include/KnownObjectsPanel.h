#pragma once
#include <iostream>
#include "ofMain.h"
#include "ofxGui.h";

using std::vector;
using std::string;
using std::function;

typedef function<void(string name)> OnItemPressCallback;

class KnownObjectsPanel : public ofxPanel {
public:
	KnownObjectsPanel();
	~KnownObjectsPanel();

	bool mousePressed(ofMouseEventArgs& args);

	void addItem(string name);
	void clearItems();

	void itemPressed(string name);
	void onItemPressed(OnItemPressCallback callback);

private:
	vector<ofxButton*> pButtons;
	OnItemPressCallback onItemPressCallback;
};