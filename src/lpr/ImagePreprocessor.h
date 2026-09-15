#pragma once
#include "types.h"
namespace lpr {
class ImagePreprocessor {
public:
    cv::Mat grayscale(const cv::Mat& image) const;
    cv::Mat edges(const cv::Mat& image, const DetectionConfig& config) const;
};
}
