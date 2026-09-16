#pragma once

#include <opencv2/core.hpp>
#include <string>
#include <vector>

namespace lpr {

struct DetectionCandidate {
    cv::RotatedRect rotated_rect;
    cv::Rect bounding_rect;
    double score = 0.0;
    double aspect_ratio = 0.0;
    double rectangularity = 0.0;
    double edge_density = 0.0;
};

struct PlateResult {
    bool found = false;
    DetectionCandidate candidate;
    cv::Mat annotated;
    cv::Mat plate_crop;
    std::string text;
    std::string status;
};

struct DetectorConfig {
    double min_area = 500.0;
    double max_area_ratio = 0.35;
    double min_aspect_ratio = 2.0;
    double max_aspect_ratio = 8.0;
    double min_rectangularity = 0.35;
    double min_score = 0.30;
    int blur_kernel = 5;
    int canny_low = 60;
    int canny_high = 180;
    int morphology_width = 21;
    int morphology_height = 5;
};

} // namespace lpr
