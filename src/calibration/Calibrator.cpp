//
// Created by Andrei Nechaev on 6/17/17.
//

#include "Calibrator.h"

calibration::Calibrator::~Calibrator() {

}

std::string calibration::Calibrator::get_source_dir() const {
    return source_;
}

int calibration::Calibrator::get_amount() const {
    return amount_;
}

void calibration::Calibrator::calibrate(cv::Mat& matrix, cv::Mat& distCoef) {
    std::vector<std::vector<cv::Point2f> > image_points;
    std::vector<std::vector<cv::Point3f> > object_points;
    get_image_points(image_points);
    fill_object_points(object_points, image_points.size());

    std::vector<cv::Mat> rvecs, tvecs;
    cv::calibrateCamera(object_points, image_points, size_, matrix, distCoef, rvecs, tvecs);
}



