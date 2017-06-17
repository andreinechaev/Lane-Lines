//
// Created by Andrei Nechaev on 6/17/17.
//

#ifndef LANELINES_CALIBRATOR_H
#define LANELINES_CALIBRATOR_H


#include <string>
#include <opencv2/opencv.hpp>

namespace calibration {
    class Calibrator {

    private:
        std::string source_;
        cv::Size size_;
        int amount_;

    protected:
        inline void get_image_points(std::vector<std::vector<cv::Point2f> > &matrix) {
            for (int i = 1; i <= amount_; i++) {
                std::stringstream path;
                path << source_ << i << ".jpg";
                auto image = cv::imread(path.str());

                assert(image.data);

                std::vector<cv::Point2f > points;
                bool found = cv::findChessboardCorners(
                        image,
                        size_,
                        points,
                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE
                );
                if (found) {
                    matrix.shrink_to_fit();
                    matrix.push_back(std::move(points));
                }
            }
        }

        inline void fill_object_points(std::vector<std::vector<cv::Point3f> > &obj_points, long images_size=0) {
            for (int k = 0; k < images_size; k++) {
                std::vector<cv::Point3f> obj;
                for (int i = 0; i < size_.height; i++) {
                    for (int j = 0; j < size_.width; j++) {
                        obj.push_back(cv::Point3f(i, j, 0));
                    }
                }
                obj_points.push_back(obj);
            }
        }

    public:
        Calibrator(std::string &source, int amount, cv::Size& size)
                : source_(source), amount_(amount), size_(size) {};

        virtual ~Calibrator();

        std::string get_source_dir() const;

        int get_amount() const;

        void calibrate(cv::Mat& matrix, cv::Mat& distCoef);
    };
}

#endif //LANELINES_CALIBRATOR_H
