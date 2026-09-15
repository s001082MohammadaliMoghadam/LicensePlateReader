#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("License Plate Reader");
    ofBackground(20, 20, 30);
}

void ofApp::update() {}

void ofApp::draw() {
    ofSetColor(255);
    ofDrawBitmapStringHighlight(statusMessage, 20, 30);
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
    if (!dragInfo.files.empty()) {
        statusMessage = "Dropped: " + dragInfo.files.front();
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'o' || key == 'O') {
        ofFileDialogResult result = ofSystemLoadDialog("Select an image");
        if (result.bSuccess) statusMessage = "Selected: " + result.getPath();
    }
}
