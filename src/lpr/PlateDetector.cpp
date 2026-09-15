#include "PlateDetector.h"
#include <algorithm>
#include <cmath>
namespace lpr {
PlateDetector::PlateDetector(DetectionConfig config):config_(config) {}
std::vector<PlateCandidate> PlateDetector::detect(const cv::Mat& image,const cv::Mat& closedEdges) const {
    std::vector<std::vector<cv::Point>> contours; cv::Mat working=closedEdges.clone(); cv::findContours(working,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
    std::vector<PlateCandidate> result; double imageArea=static_cast<double>(image.rows*image.cols);
    for(const auto& contour:contours){ double area=cv::contourArea(contour); if(area<=0)continue; cv::RotatedRect rect=cv::minAreaRect(contour); double w=rect.size.width,h=rect.size.height; double aspect=std::max(w,h)/std::max(1.0,std::min(w,h)); double boxArea=std::max(1.0,w*h); double rectangularity=area/boxArea; double areaRatio=area/imageArea; if(aspect<config_.min_aspect_ratio||aspect>config_.max_aspect_ratio||areaRatio<config_.min_area_ratio||areaRatio>config_.max_area_ratio||rectangularity<config_.min_rectangularity)continue; double aspectScore=1.0-std::min(1.0,std::abs(aspect-4.7)/4.7); double score=.45*aspectScore+.35*rectangularity+.20*std::min(1.0,areaRatio/.05); result.push_back({rect,score,aspect,rectangularity,areaRatio}); }
    std::sort(result.begin(),result.end(),[](const auto&a,const auto&b){return a.score>b.score;}); return result;
}
cv::Mat PlateDetector::cropCandidate(const cv::Mat& image,const PlateCandidate& c) const { cv::Rect box=c.rectangle.boundingRect()&cv::Rect(0,0,image.cols,image.rows); return box.area()>0?image(box).clone():cv::Mat(); }
}
