#include "KnownObjectsPanel.h";

KnownObjectsPanel::KnownObjectsPanel(float x, float y, float width, float height) {
	this->setPosition(x, y);
	this->setDimensions(width, height);

	ofAddListener(ofEvents().mousePressed, this, &KnownObjectsPanel::mousePressed);
}

KnownObjectsPanel::~KnownObjectsPanel() {
	ofRemoveListener(ofEvents().mousePressed, this, &KnownObjectsPanel::mousePressed);
}

void KnownObjectsPanel::addItem(string name) {
	this->items.push_back(name);
}

void KnownObjectsPanel::clearItems() {
	this->items.clear();
}

void KnownObjectsPanel::removeItem(string name) {
	int itemIndex;
	for (int i = 0; i < this->items.size(); i++) {
		if (this->items.at(i) == name) {
			itemIndex = i;
			break;
		}
	}

	this->items.erase(this->items.begin() + itemIndex);
}

void KnownObjectsPanel::draw() {
	this->draw(this->x, this->y);
}

void KnownObjectsPanel::draw(float x, float y) {
	ofSetColor(0, 0, 0);
	ofDrawRectangle(x, y, this->width, this->height);
	ofDrawBitmapString("Tracked objects", x + width / 5, y + height / 10);

	for (int i = 0; i < this->items.size(); i++) {
		ofDrawBitmapString(items.at(i), x + width / 10, y + (i + 2) * (height / 10));
	}
}

void KnownObjectsPanel::mousePressed(ofMouseEventArgs& args) {
	ofRectangle thisArea(x, y, width, height);
	if (!thisArea.inside(args.x, args.y)) return;
}

void KnownObjectsPanel::setDimensions(float width, float height) {
	this->width = width;
	this->height = height;
}

void KnownObjectsPanel::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void KnownObjectsPanel::setup(float x, float y, float width, float height) {
	this->setPosition(x, y);
	this->setDimensions(width, height);
}