#include "ImagePreprocessor.h"
#include <opencv2/imgproc.hpp>
#include <stdexcept>
#include <utility>

namespace lpr {

ImagePreprocessor::ImagePreprocessor(DetectorConfig config) : config_(std::move(config)) {
    if (config_.blur_kernel < 3 || config_.blur_kernel % 2 == 0) config_.blur_kernel = 5;
    if (config_.morphology_width < 1) config_.morphology_width = 21;
    if (config_.morphology_height < 1) config_.morphology_height = 5;
}

cv::Mat ImagePreprocessor::grayscale(const cv::Mat& input) const {
    if (input.empty()) throw std::invalid_argument("ImagePreprocessor received an empty image");
    cv::Mat gray;
    if (input.channels() == 1) gray = input.clone();
    else if (input.channels() == 3) cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    else if (input.channels() == 4) cv::cvtColor(input, gray, cv::COLOR_BGRA2GRAY);
    else throw std::invalid_argument("Unsupported image channel count");
    return gray;
}

cv::Mat ImagePreprocessor::edges(const cv::Mat& input) const {
    cv::Mat gray = grayscale(input), blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(config_.blur_kernel, config_.blur_kernel), 0.0);
    cv::Mat result;
    cv::Canny(blurred, result, config_.canny_low, config_.canny_high);
    return result;
}

cv::Mat ImagePreprocessor::plateMask(const cv::Mat& input) const {
    cv::Mat closed;
    const cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,
        cv::Size(config_.morphology_width, config_.morphology_height));
    cv::morphologyEx(edges(input), closed, cv::MORPH_CLOSE, kernel);
    return closed;
}

} // namespace lpr
