#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofGLWindowSettings settings;
    settings.setSize(1280, 800);
    settings.windowMode = OF_WINDOW;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
