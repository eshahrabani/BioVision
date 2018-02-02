#include "KnownObjectsPanel.h";

KnownObjectsPanel::KnownObjectsPanel(float x, float y, float width, float height) {
	this->setPosition(x, y);
	this->setDimensions(width, height);

	ofAddListener(ofEvents().mousePressed, this, &KnownObjectsPanel::mousePressed);
}

KnownObjectsPanel::~KnownObjectsPanel() {
	ofRemoveListener(ofEvents().mousePressed, this, &KnownObjectsPanel::mousePressed);
}

void KnownObjectsPanel::draw() {
	this->draw(this->x, this->y);
}

void KnownObjectsPanel::draw(float x, float y) {
	ofSetColor(255, 255, 255);
	ofDrawRectangle(x, y, this->width, this->height);

	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Tracked objects", x + width / 4, y + height / 10);
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