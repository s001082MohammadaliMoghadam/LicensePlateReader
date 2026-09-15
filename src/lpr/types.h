#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include <opencv2/opencv.hpp>
#include <string>
namespace lpr {
struct DetectionConfig {
    double min_area_ratio = 0.002;
    double max_area_ratio = 0.50;
    double min_aspect_ratio = 2.0;
    double max_aspect_ratio = 6.5;
    double min_rectangularity = 0.35;
    int canny_low = 60;
    int canny_high = 180;
    cv::Size closing_kernel = cv::Size(17, 3);
};
struct PlateCandidate {
    cv::RotatedRect rectangle;
    double score = 0.0;
    double aspect_ratio = 0.0;
    double rectangularity = 0.0;
    double area_ratio = 0.0;
};
struct ReaderResult {
    bool found = false;
    PlateCandidate candidate;
    cv::Mat plate_crop;
    std::string recognized_text;
    std::string message;
};
}
