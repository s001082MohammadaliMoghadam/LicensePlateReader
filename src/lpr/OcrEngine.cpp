#include "OcrEngine.h"
namespace lpr {
std::string PlaceholderOcrEngine::recognize(const cv::Mat& plate_image) {
    if (plate_image.empty()) return {};
    return "OCR_NOT_CONFIGURED";
}
} // namespace lpr
