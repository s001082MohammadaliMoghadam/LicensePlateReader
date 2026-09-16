#include "LicensePlateReader.h"
#include <stdexcept>
#include <utility>
namespace lpr {
LicensePlateReader::LicensePlateReader(DetectorConfig config, std::unique_ptr<OcrEngine> ocr)
    : preprocessor_(config), detector_(config), ocr_(std::move(ocr)) {
    if (!ocr_) throw std::invalid_argument("LicensePlateReader requires an OCR engine");
}
PlateResult LicensePlateReader::process(const cv::Mat& image) const {
    PlateResult result;
    if (image.empty()) { result.status = "Input image is empty"; return result; }
    const cv::Mat mask = preprocessor_.plateMask(image);
    result = detector_.detect(image, mask);
    if (result.found) {
        result.text = ocr_->recognize(result.plate_crop);
        result.status += "; OCR: " + result.text;
    }
    return result;
}
} // namespace lpr
