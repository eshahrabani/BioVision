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
	vector<string> getNames();
	void clearItems();

	void onItemPressed(OnItemPressCallback callback);

private:
	void itemPressed(string name);
	vector<ofxButton*> pButtons;
	vector<string> buttonNames;
	OnItemPressCallback onItemPressCallback;
};