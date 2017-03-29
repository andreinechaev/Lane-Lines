#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    auto image = cv::imread("data/signs_vehicles_xygrad.png");

    assert(image.data);

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::imshow("Greyscale", gray);
    cv::waitKey(0);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}