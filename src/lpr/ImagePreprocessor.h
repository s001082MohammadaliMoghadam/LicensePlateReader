#pragma once

#include "types.h"
#include <opencv2/core.hpp>

namespace lpr {

class ImagePreprocessor {
public:
    explicit ImagePreprocessor(DetectorConfig config = {});
    cv::Mat grayscale(const cv::Mat& input) const;
    cv::Mat edges(const cv::Mat& input) const;
    cv::Mat plateMask(const cv::Mat& input) const;
private:
    DetectorConfig config_;
};

} // namespace lpr
