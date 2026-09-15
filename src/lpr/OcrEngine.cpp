#include "OcrEngine.h"
namespace lpr {
std::string PlaceholderOcr::recognize(const cv::Mat& plate) const {
    return plate.empty() ? "" : "OCR_NOT_CONFIGURED";
}
}
