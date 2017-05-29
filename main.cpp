#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

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

void get_image_points(std::vector<std::vector<cv::Point2f> > &matrix, cv::Size size = cv::Size(9, 6)) {
    for (int i = 1; i <= 20; i++) {
        std::stringstream path;
        path << "calibration/calibration" << i << ".jpg";
        auto image = cv::imread(path.str());
        std::vector<cv::Point2f > points;
        bool found = cv::findChessboardCorners(
                image,
                size,
                points,
                cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE
        );
        if (found) matrix.push_back(points);
    }
}

void get_object_points(std::vector<std::vector<cv::Point3f> > &obj_points, long images_size=0, cv::Size size = cv::Size(9, 6)) {
    for (int k = 0; k < images_size; k++) {
        std::vector<cv::Point3f> obj;
        for (int i = 0; i < size.height; i++) {
            for (int j = 0; j < size.width; j++) {
                obj.push_back(cv::Point3f(i, j, 0));
            }
        }
        obj_points.push_back(obj);
    }
}

int main() {
    auto size = cv::Size(9, 6);
    std::vector<std::vector<cv::Point2f> > img_points;
    get_image_points(img_points);

    std::vector<std::vector<cv::Point3f>> obj_points;
    get_object_points(obj_points, img_points.size());

    cv::Mat matrix, distCoef;
    std::vector<cv::Mat> rvecs, tvecs;
    cv::calibrateCamera(obj_points, img_points, size, matrix, distCoef, rvecs, tvecs);

    // Testing undistortion functionality on gotten matrix
    auto test_img = cv::imread("calibration/calibration2.jpg");
    cv::Mat dst_img;
    cv::undistort(test_img, dst_img, matrix, distCoef);

    cv::imshow("Undistorted", dst_img);
    cv::waitKey(0);

    auto image = cv::imread("data/signs_vehicles_xygrad.png");
    assert(image.data);

//    cv::GaussianBlur(image, image, cv::Size(3,3), 0);
    auto gray = set_color_schema(image);
    cv::imshow("Greyscale", gray);
    cv::waitKey(0);

    auto grad = abs_sobel_thresh(image, 'x', 3);
    cv::imshow("Grad X", grad);
    cv::waitKey(0);

    std::cout << "End of program" << std::endl;
    return 0;
}