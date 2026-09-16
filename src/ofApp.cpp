#include "ofApp.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <exception>
#include <string>

namespace {

ofImage matToOfImage(const cv::Mat& image) {
    ofImage output;
    if (image.empty()) return output;

    cv::Mat rgba;
    switch (image.channels()) {
    case 1:
        cv::cvtColor(image, rgba, cv::COLOR_GRAY2RGBA);
        break;
    case 3:
        cv::cvtColor(image, rgba, cv::COLOR_BGR2RGBA);
        break;
    case 4:
        cv::cvtColor(image, rgba, cv::COLOR_BGRA2RGBA);
        break;
    default:
        return output;
    }

    output.allocate(rgba.cols, rgba.rows, OF_IMAGE_COLOR_ALPHA);
    output.setFromPixels(rgba.ptr<unsigned char>(), rgba.cols, rgba.rows,
                         OF_IMAGE_COLOR_ALPHA);
    output.update();
    return output;
}

} // namespace

void ofApp::setup() {
    ofSetWindowTitle("License Plate Reader");
    ofSetWindowShape(1280, 800);
    ofSetFrameRate(60);
    status_ = "Ready. Press O to choose a vehicle image.";
}

void ofApp::update() {}

void ofApp::draw() {
    ofBackground(24, 28, 36);
    ofSetColor(255);

    ofDrawBitmapStringHighlight("License Plate Reader", 24, 32);
    ofDrawBitmapStringHighlight("Press O to choose an image, or drag an image into this window", 24, 56);
    ofDrawBitmapStringHighlight(status_, 24, 80);

    const float margin = 24.0f;
    const float top = 110.0f;
    const float gap = 16.0f;
    const float panel_width = (ofGetWidth() - 2.0f * margin - 2.0f * gap) / 3.0f;
    const float panel_height = ofGetHeight() - top - margin;

    auto drawPanel = [&](const ofImage& image, const std::string& label, float x) {
        ofSetColor(48, 54, 66);
        ofDrawRectangle(x, top, panel_width, panel_height);
        ofSetColor(255);
        ofDrawBitmapString(label, x + 10.0f, top + 22.0f);

        if (!image.isAllocated() || image.getWidth() <= 0 || image.getHeight() <= 0) return;

        const float available_width = panel_width - 20.0f;
        const float available_height = panel_height - 45.0f;
        const float scale = std::min(available_width / static_cast<float>(image.getWidth()),
                                     available_height / static_cast<float>(image.getHeight()));
        if (scale <= 0.0f) return;

        const float width = image.getWidth() * scale;
        const float height = image.getHeight() * scale;
        image.draw(x + (panel_width - width) * 0.5f,
                   top + 35.0f + (available_height - height) * 0.5f,
                   width, height);
    };

    drawPanel(original_image_, "Original", margin);
    drawPanel(annotated_image_, "Annotated", margin + panel_width + gap);
    drawPanel(crop_image_, "Plate crop", margin + 2.0f * (panel_width + gap));
}

void ofApp::keyPressed(int key) {
    if (key != 'o' && key != 'O') return;

    status_ = "Opening file dialog...";
    ofFileDialogResult dialog = ofSystemLoadDialog("Choose a vehicle image", false);
    if (!dialog.bSuccess) {
        status_ = "File selection cancelled.";
        return;
    }

    loadAndProcess(dialog.getPath());
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
    if (dragInfo.files.empty()) {
        status_ = "No file was dropped.";
        return;
    }

    loadAndProcess(dragInfo.files.front().string());
}

void ofApp::loadAndProcess(const std::string& path) {
    if (path.empty()) {
        status_ = "Empty file path.";
        return;
    }

    status_ = "Loading image...";

    try {
        const cv::Mat input = cv::imread(path, cv::IMREAD_COLOR);
        if (input.empty()) {
            status_ = "Could not load image: " + path;
            return;
        }

        original_image_ = matToOfImage(input);
        if (!original_image_.isAllocated()) {
            status_ = "Could not convert input image for display.";
            return;
        }

        status_ = "Running plate detector...";
        const lpr::PlateResult result = reader_.process(input);
        annotated_image_ = matToOfImage(result.annotated);
        crop_image_ = matToOfImage(result.plate_crop);
        status_ = result.status.empty() ? "Processing finished." : result.status;
    } catch (const cv::Exception& error) {
        status_ = std::string("OpenCV error: ") + error.what();
    } catch (const std::exception& error) {
        status_ = std::string("C++ error: ") + error.what();
    } catch (...) {
        status_ = "Unknown processing error.";
    }
}
