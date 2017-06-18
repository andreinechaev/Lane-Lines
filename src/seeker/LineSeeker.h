//
// Created by Andrei Nechaev on 6/17/17.
//

#ifndef LANELINES_LINESEEKER_H
#define LANELINES_LINESEEKER_H

#include <opencv2/opencv.hpp>

namespace seeker {
    class LineSeeker {
    private:
        int kernel_size_;

    public:
        LineSeeker(int kernel_size=3): kernel_size_(kernel_size){}
        virtual ~LineSeeker(){}

        cv::Mat abs_sobel_thresh(cv::Mat& src, const char orient='x', int mag_min=255, bool is_gray = false) const;

        cv::Mat mag_thresh(cv::Mat& src, short mag_min=0, short mag_max=255, bool is_gray=false) const;

        cv::Mat dir_thresh(cv::Mat& src, double mag_min=0.f, double mag_max=CV_PI/2, bool is_gray=false);
    };
}


#endif //LANELINES_LINESEEKER_H
