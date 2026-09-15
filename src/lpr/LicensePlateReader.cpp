#include "LicensePlateReader.h"
namespace lpr {
LicensePlateReader::LicensePlateReader(DetectionConfig c,const OcrEngine* ocr):config_(c),detector_(c),ocr_(ocr){}
ReaderResult LicensePlateReader::process(const cv::Mat& image) const { ReaderResult out; if(image.empty()){out.message="Input image is empty";return out;} cv::Mat edge=preprocessor_.edges(image,config_); cv::Mat closed=preprocessor_.closeEdges(edge,config_); auto candidates=detector_.detect(image,closed); if(candidates.empty()){out.message="No plate-like candidate found";return out;} out.found=true;out.candidate=candidates.front();out.plate_crop=detector_.cropCandidate(image,out.candidate);out.recognized_text=ocr_?ocr_->recognize(out.plate_crop):"OCR_NOT_CONFIGURED";out.message="Candidate detected";return out; }
void LicensePlateReader::annotate(cv::Mat& image,const PlateCandidate& c,const std::string& text){cv::Point2f pts[4];c.rectangle.points(pts);for(int i=0;i<4;i++)cv::line(image,pts[i],pts[(i+1)%4],cv::Scalar(0,255,0),3);cv::putText(image,text,pts[0],cv::FONT_HERSHEY_SIMPLEX,.9,cv::Scalar(0,255,0),2);}
}
