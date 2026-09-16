#pragma once

#include "ofMain.h"
#include "lpr/LicensePlateReader.h"

#include <string>

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void dragEvent(ofDragInfo dragInfo) override;

private:
    void loadAndProcess(const std::string& path);

    lpr::LicensePlateReader reader_;
    ofImage original_image_;
    ofImage annotated_image_;
    ofImage crop_image_;
    std::string status_;
};
