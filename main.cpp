#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "src/calibration/Calibrator.h"
#include "src/seeker/LineSeeker.h"

using namespace std::chrono;
typedef std::chrono::high_resolution_clock hires_clk;

void imshow(cv::Mat &image, std::string name) {
//    cv::namedWindow(name, cv::WINDOW_AUTOSIZE); // required for built from source opencv for anaconda
    cv::imshow(name, image);
    cv::waitKey(0);
}

//  An example of Calibrating camera with Calibrator class
void calibrate(cv::Mat& matrix, cv::Mat& distCoef) {
    auto start = hires_clk::now();

    auto size = cv::Size(9, 6);
    std::string path = "calibration/calibration";
    calibration::Calibrator calibrator(path, 20, size);
    calibrator.calibrate(matrix, distCoef);

    auto end = hires_clk::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Calibration duration: " << duration / 1000.f << " secs \n";

    // saving calibration matrix & distance coefficient
    calibration::Calibrator::save(matrix, distCoef);
}

int main() {
    cv::Mat matrix, distCoef;
    // loading calibration matrix & distance coefficient
    calibration::Calibrator::load(matrix, distCoef);

    auto src_image = cv::imread("data/signs_vehicles_xygrad.png");
    cv::GaussianBlur(src_image, src_image, cv::Size(3,3), 0);
    cv::Mat dst;
    cv::undistort(src_image, dst, matrix, distCoef);
    assert(dst.data);


    seeker::LineSeeker lineSeeker;
    auto grad = lineSeeker.abs_sobel_thresh(dst, 'x', 120);
    imshow(grad, "Absolute Sobel Threshold");
    auto mag = lineSeeker.mag_thresh(dst, 30, 120);
    imshow(mag, "Magnitude");
    cv::destroyAllWindows();

    std::cout << "End of program" << std::endl;
    return 0;
}