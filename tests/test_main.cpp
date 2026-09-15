#include "lpr/LicensePlateReader.h"
#include <cassert>
#include <iostream>
int main() {
    cv::Mat image(300, 600, CV_8UC3, cv::Scalar(30, 30, 30));
    cv::rectangle(image, cv::Rect(180, 130, 240, 50), cv::Scalar(240, 240, 240), cv::FILLED);
    cv::putText(image, "B MW 1234", cv::Point(190, 165), cv::FONT_HERSHEY_SIMPLEX, .8, cv::Scalar(10, 10, 10), 2);
    lpr::LicensePlateReader reader;
    auto result = reader.process(image);
    assert(result.found);
    assert(!result.plate_crop.empty());
    std::cout << "basic detector test passed\n";
}
