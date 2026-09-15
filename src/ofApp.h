#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void dragEvent(ofDragInfo dragInfo) override;
    void keyPressed(int key) override;

    std::string statusMessage = "Drag an image here or press O to open one.";
};
