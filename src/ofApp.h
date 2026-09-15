#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "lpr/LicensePlateReader.h"
#include "lpr/OcrEngine.h"
class ofApp:public ofBaseApp{
public:
 void setup() override; void update() override; void draw() override; void dragEvent(ofDragInfo dragInfo) override; void keyPressed(int key) override;
 void loadAndProcess(const std::string& path);
 ofImage originalImage,annotatedImage,plateCropImage; lpr::PlaceholderOcr ocr; lpr::LicensePlateReader reader{lpr::DetectionConfig(),nullptr}; std::string statusMessage="Drag an image here or press O to open one."; bool hasResult=false;
};
