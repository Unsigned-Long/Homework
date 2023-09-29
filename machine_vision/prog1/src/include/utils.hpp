// Copyright (c) 2023. Created on 9/29/23 10:27 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef EXTRACTOR_UTILS_HPP
#define EXTRACTOR_UTILS_HPP

#include "Eigen/Dense"
#include "cereal/cereal.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace Eigen {
    template<class Archive, typename ScaleType, int Rows, int Cols>
    void serialize(Archive &archive, Eigen::Matrix<ScaleType, Rows, Cols> &m) {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                archive(cereal::make_nvp('r' + std::to_string(i) + 'c' + std::to_string(j), m(i, j)));
            }
        }
    }

    template<class Archive, typename ScaleType, int Cols>
    void serialize(Archive &archive, Eigen::Matrix<ScaleType, Eigen::Dynamic, Cols> &m) {
        for (int i = 0; i < m.rows(); ++i) {
            for (int j = 0; j < Cols; ++j) {
                archive(cereal::make_nvp('r' + std::to_string(i) + 'c' + std::to_string(j), m(i, j)));
            }
        }
    }

    template<class Archive, typename ScaleType>
    void serialize(Archive &archive, Eigen::Matrix<ScaleType, Eigen::Dynamic, Eigen::Dynamic> &m) {
        for (int i = 0; i < m.rows(); ++i) {
            for (int j = 0; j < m.cols(); ++j) {
                archive(cereal::make_nvp('r' + std::to_string(i) + 'c' + std::to_string(j), m(i, j)));
            }
        }
    }
}

namespace ns_mv {
    static cv::Mat ConvertToVisibleMat(const cv::Mat &fImg) {
        double min, max;
        cv::minMaxIdx(fImg, &min, &max);
        cv::Mat adjMap;
        fImg.convertTo(adjMap, CV_8UC3, 255 / (max - min), -min);
        cv::Mat falseColorsMap;
        cv::applyColorMap(adjMap, falseColorsMap, cv::COLORMAP_COOL);
        return adjMap;
    }

    static void ShowImg(const cv::Mat &img, const std::string &winName = "win") {
        cv::namedWindow(winName, cv::WindowPropertyFlags::WND_PROP_ASPECT_RATIO);
        cv::imshow(winName, img);
        cv::waitKey(0);
    }

}


#endif //EXTRACTOR_UTILS_HPP
