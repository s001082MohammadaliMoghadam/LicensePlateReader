#pragma once
#include "ImagePreprocessor.h"
#include "PlateDetector.h"
#include "OcrEngine.h"
namespace lpr {
class LicensePlateReader {
public:
    LicensePlateReader(DetectionConfig config=DetectionConfig(),const OcrEngine* ocr=nullptr);
    ReaderResult process(const cv::Mat& image) const;
    static void annotate(cv::Mat& image,const PlateCandidate& candidate,const std::string& text);
private:
    DetectionConfig config_;
    ImagePreprocessor preprocessor_;
    PlateDetector detector_;
    const OcrEngine* ocr_;
};
}
