#include "KnownObjectsPanel.h"

KnownObjectsPanel::KnownObjectsPanel() {
	
}

KnownObjectsPanel::~KnownObjectsPanel() {
	// Delete all buttons.
	for (ofxButton* pButton : this->pButtons) {
		delete pButton;
	}
}

bool KnownObjectsPanel::mousePressed(ofMouseEventArgs& args) {
	float x = args.x;
	float y = args.y;

	// (x, y) should be inside the panel.
	if (this->getShape().inside(x, y)) {
		for (ofxButton* pButton : this->pButtons) {
			if (pButton->getShape().inside(x, y)) {
				// Clicked inside this button.
				this->itemPressed(pButton->getName());
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void KnownObjectsPanel::addItem(string name) {
	ofxButton* pButton = new ofxButton();
	
	pButton->setup(name);

	this->pButtons.push_back(pButton);
	this->add(pButton);
}

void KnownObjectsPanel::clearItems() {
	/* 
	 * Clears the buttons from the superclass.
	 * We still have the pointers in this class, so we can delete them on destruction.
	*/
	this->clear();
}

void KnownObjectsPanel::itemPressed(string name) {
	if (this->onItemPressCallback) {
		this->onItemPressCallback(name);
	}
}

void KnownObjectsPanel::onItemPressed(OnItemPressCallback callback) {
	this->onItemPressCallback = callback;
}


