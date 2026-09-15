#include "ImagePreprocessor.h"
namespace lpr {
cv::Mat ImagePreprocessor::grayscale(const cv::Mat& image) const {
    cv::Mat gray;
    if (image.channels() == 1) gray = image.clone();
    else cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}
cv::Mat ImagePreprocessor::edges(const cv::Mat& image, const DetectionConfig& config) const {
    cv::Mat gray = grayscale(image), blurred, edgeImage;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
    cv::Canny(blurred, edgeImage, config.canny_low, config.canny_high);
    return edgeImage;
}
}
