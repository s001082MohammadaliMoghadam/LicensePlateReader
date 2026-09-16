#pragma once
#include "types.h"
#include <opencv2/core.hpp>
#include <vector>
namespace lpr {
class PlateDetector {
public:
    explicit PlateDetector(DetectorConfig config = {});
    std::vector<DetectionCandidate> findCandidates(const cv::Mat& image, const cv::Mat& mask) const;
    PlateResult detect(const cv::Mat& image, const cv::Mat& mask) const;
private:
    DetectorConfig config_;
    DetectionCandidate scoreContour(const cv::Mat& contour_image, const std::vector<cv::Point>& contour) const;
    double contourEdgeDensity(const cv::Mat& edges, const cv::Rect& rect) const;
};
} // namespace lpr
