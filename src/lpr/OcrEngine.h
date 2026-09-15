#pragma once
#include "types.h"
namespace lpr {
class OcrEngine {
public:
    virtual ~OcrEngine() = default;
    virtual std::string recognize(const cv::Mat& plate) const = 0;
};
class PlaceholderOcr final : public OcrEngine {
public:
    std::string recognize(const cv::Mat& plate) const override;
};
}
