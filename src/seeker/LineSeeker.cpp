//
// Created by Andrei Nechaev on 6/17/17.
//

#include "LineSeeker.h"

cv::Mat seeker::LineSeeker::abs_sobel_thresh(cv::Mat &src, const char orient, int mag_min, bool is_gray) const {
    cv::Mat gray;
    if (!is_gray) {
        cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    } else {
        gray = src;
    }
    cv::Mat dst;
    if (orient == 'x') {
        cv::Sobel(gray, dst, CV_64F, 1, 0, kernel_size_);
    } else {
        cv::Sobel(gray, dst, CV_64F, 0, 1, kernel_size_);
    }

    cv::Mat abs_grad;
    cv::convertScaleAbs(dst, abs_grad);
    cv::Mat bin;
    cv::threshold(abs_grad, bin, mag_min, 255.0, cv::THRESH_BINARY);
    return bin;
}

cv::Mat seeker::LineSeeker::mag_thresh(cv::Mat &src, short mag_min, short mag_max, bool is_gray) const {
    cv::Mat gray;
    if (!is_gray) {
        cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    } else {
        gray = src;
    }
    cv::Mat grad_x, grad_y;
    cv::Sobel(gray, grad_x, CV_64F, 1, 0, kernel_size_);
    cv::Sobel(gray, grad_y, CV_64F, 0, 1, kernel_size_);

    cv::Mat mag(cv::Size(mag_min, mag_max), grad_x.type());
    cv::magnitude(grad_x, grad_y, mag);
    cv::Mat bin;
    cv::threshold(mag, bin, mag_max, 255.0, cv::THRESH_BINARY);
    return bin;
}

cv::Mat seeker::LineSeeker::dir_thresh(cv::Mat &src, double mag_min, double mag_max, bool is_gray) {
    cv::Mat gray;
    if (!is_gray) {
        cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    } else {
        gray = src;
    }
    cv::Mat grad_x, grad_y;
    cv::Sobel(gray, grad_x, CV_64F, 1, 0, kernel_size_);
    cv::Sobel(gray, grad_y, CV_64F, 0, 1, kernel_size_);
    cv::Mat abs_grad_dir;
    cv::phase(grad_x, grad_y, abs_grad_dir);

    cv::Mat bin;
    cv::threshold(src, bin, mag_min, mag_max, cv::THRESH_BINARY);
    return bin;
}
