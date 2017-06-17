#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "src/calibration/Calibrator.h"

using namespace std::chrono;
typedef std::chrono::high_resolution_clock hires_clk;

cv::Mat set_color_schema(cv::Mat &image, cv::ColorConversionCodes color_code = cv::COLOR_BGR2GRAY) {
    cv::Mat gray;
    cv::cvtColor(image, gray, color_code);
    return gray;
}

cv::Mat abs_sobel_thresh(cv::Mat &image, char orient='x', int sobel_kernel=3, short min=0, short max=255) {
    auto gray = set_color_schema(image);

    cv::Mat dst;
    if (orient == 'x') {
        cv::Sobel(gray, dst, CV_64F, 1, 0, sobel_kernel);

    } else {
        cv::Sobel(gray, dst, CV_64F, 0, 1, sobel_kernel);
    }

    cv::Mat abs_grad;
    cv::convertScaleAbs(dst, abs_grad);

    return abs_grad;
}

void imshow(cv::Mat &image, std::string name) {
//    cv::namedWindow(name, cv::WINDOW_OPENGL); // required for built from source opencv for anaconda
    cv::imshow(name, image);
    cv::waitKey(0);
}

int main() {
    auto start = hires_clk::now();

    auto size = cv::Size(9, 6);

    std::string path = "calibration/calibration";
    cv::Mat matrix, distCoef;
    calibration::Calibrator calibrator(path, 20, size);
    calibrator.calibrate(matrix, distCoef);

    auto end = hires_clk::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Calibration duration: " << duration / 1000.f << " secs \n";

    auto src_image = cv::imread("data/signs_vehicles_xygrad.png");
    cv::Mat dst;
    cv::undistort(src_image, dst, matrix, distCoef);
    assert(dst.data);

//    cv::GaussianBlur(image, image, cv::Size(3,3), 0);
    auto gray = set_color_schema(dst);
    imshow(gray, "Greyscale");

    auto grad = abs_sobel_thresh(dst, 'x', 3);
    imshow(grad, "Grad X");

    cv::destroyAllWindows();

    std::cout << "End of program" << std::endl;
    return 0;
}