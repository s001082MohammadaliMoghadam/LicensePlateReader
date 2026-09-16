#pragma once
#include "ImagePreprocessor.h"
#include "OcrEngine.h"
#include "PlateDetector.h"
#include "types.h"
#include <memory>
namespace lpr {
class LicensePlateReader {
public:
    explicit LicensePlateReader(DetectorConfig config = {}, std::unique_ptr<OcrEngine> ocr = std::make_unique<PlaceholderOcrEngine>());
    PlateResult process(const cv::Mat& image) const;
private:
    ImagePreprocessor preprocessor_;
    PlateDetector detector_;
    std::unique_ptr<OcrEngine> ocr_;
};
} // namespace lpr
