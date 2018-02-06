#include "KnownObjectsPanel.h"

KnownObjectsPanel::KnownObjectsPanel() {
	
}

KnownObjectsPanel::~KnownObjectsPanel() {
	// Delete all buttons.
	for (ofxButton* pButton : this->pButtons) {
		delete pButton;
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

bool KnownObjectsPanel::mousePressed(ofMouseEventArgs& args) {
	return true;
}