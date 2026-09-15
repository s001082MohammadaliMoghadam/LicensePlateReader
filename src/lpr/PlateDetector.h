#pragma once
#include "types.h"
#include <vector>
namespace lpr {
class PlateDetector {
public:
    explicit PlateDetector(DetectionConfig config=DetectionConfig());
    std::vector<PlateCandidate> detect(const cv::Mat& image,const cv::Mat& closedEdges) const;
    cv::Mat cropCandidate(const cv::Mat& image,const PlateCandidate& candidate) const;
private:
    DetectionConfig config_;
};
}
