#pragma once
#include <opencv2/core.hpp>
#include <string>
namespace lpr {
class OcrEngine {
public:
    virtual ~OcrEngine() = default;
    virtual std::string recognize(const cv::Mat& plate_image) = 0;
};
class PlaceholderOcrEngine final : public OcrEngine {
public:
    std::string recognize(const cv::Mat& plate_image) override;
};
} // namespace lpr
