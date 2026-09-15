#include "ImagePreprocessor.h"
namespace lpr {
cv::Mat ImagePreprocessor::grayscale(const cv::Mat& image) const { cv::Mat gray; if (image.channels()==1) gray=image.clone(); else cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY); return gray; }
cv::Mat ImagePreprocessor::edges(const cv::Mat& image,const DetectionConfig& c) const { cv::Mat gray=grayscale(image),blurred,edges; cv::GaussianBlur(gray,blurred,cv::Size(5,5),0); cv::Canny(blurred,edges,c.canny_low,c.canny_high); return edges; }
cv::Mat ImagePreprocessor::closeEdges(const cv::Mat& edgeImage,const DetectionConfig& c) const { cv::Mat result; cv::Mat kernel=cv::getStructuringElement(cv::MORPH_RECT,c.closing_kernel); cv::morphologyEx(edgeImage,result,cv::MORPH_CLOSE,kernel); return result; }
}
