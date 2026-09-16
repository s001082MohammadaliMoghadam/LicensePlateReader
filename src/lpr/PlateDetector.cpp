#include "PlateDetector.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cmath>
#include <utility>
namespace lpr {
namespace {
double clamp01(double value) { return std::max(0.0, std::min(1.0, value)); }
double rangeScore(double value, double lower, double upper) {
    if (value < lower || value > upper) return 0.0;
    const double center = (lower + upper) * 0.5;
    const double half = (upper - lower) * 0.5;
    return half > 0.0 ? clamp01(1.0 - std::abs(value - center) / half) : 1.0;
}
}
PlateDetector::PlateDetector(DetectorConfig config) : config_(std::move(config)) {}
double PlateDetector::contourEdgeDensity(const cv::Mat& edges, const cv::Rect& rect) const {
    const cv::Rect safe = rect & cv::Rect(0, 0, edges.cols, edges.rows);
    if (safe.empty()) return 0.0;
    return static_cast<double>(cv::countNonZero(edges(safe))) / static_cast<double>(edges(safe).total());
}
DetectionCandidate PlateDetector::scoreContour(const cv::Mat& contour_image, const std::vector<cv::Point>& contour) const {
    DetectionCandidate c;
    c.bounding_rect = cv::boundingRect(contour);
    const double area = cv::contourArea(contour);
    const double rect_area = static_cast<double>(c.bounding_rect.area());
    c.rotated_rect = cv::minAreaRect(contour);
    const double width = std::max(c.rotated_rect.size.width, c.rotated_rect.size.height);
    const double height = std::min(c.rotated_rect.size.width, c.rotated_rect.size.height);
    c.aspect_ratio = height > 0.0 ? width / height : 0.0;
    c.rectangularity = rect_area > 0.0 ? area / rect_area : 0.0;
    c.edge_density = contourEdgeDensity(contour_image, c.bounding_rect);
    c.score = 0.50 * rangeScore(c.aspect_ratio, config_.min_aspect_ratio, config_.max_aspect_ratio)
            + 0.30 * clamp01(c.rectangularity) + 0.20 * clamp01(c.edge_density * 3.0);
    return c;
}
std::vector<DetectionCandidate> PlateDetector::findCandidates(const cv::Mat& image, const cv::Mat& mask) const {
    std::vector<DetectionCandidate> out;
    if (image.empty() || mask.empty()) return out;
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    const double image_area = static_cast<double>(image.cols * image.rows);
    for (const auto& contour : contours) {
        const double area = cv::contourArea(contour);
        if (area < config_.min_area || area > image_area * config_.max_area_ratio) continue;
        DetectionCandidate c = scoreContour(mask, contour);
        if (c.aspect_ratio < config_.min_aspect_ratio || c.aspect_ratio > config_.max_aspect_ratio
            || c.rectangularity < config_.min_rectangularity || c.score < config_.min_score) continue;
        out.push_back(c);
    }
    std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) { return a.score > b.score; });
    return out;
}
PlateResult PlateDetector::detect(const cv::Mat& image, const cv::Mat& mask) const {
    PlateResult result;
    if (image.empty()) { result.status = "No image provided"; return result; }
    result.annotated = image.clone();
    const auto candidates = findCandidates(image, mask);
    if (candidates.empty()) { result.status = "No plate candidate detected"; return result; }
    result.found = true;
    result.candidate = candidates.front();
    const cv::Rect crop = result.candidate.bounding_rect & cv::Rect(0, 0, image.cols, image.rows);
    result.plate_crop = image(crop).clone();
    cv::rectangle(result.annotated, crop, cv::Scalar(0, 255, 0), 3);
    result.status = "Plate candidate detected";
    return result;
}
} // namespace lpr
