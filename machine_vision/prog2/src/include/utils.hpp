// Copyright (c) 2023. Created on 9/29/23 10:27 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef EXTRACTOR_UTILS_HPP
#define EXTRACTOR_UTILS_HPP

#include "cereal/cereal.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace cv {
    template<class Archive, typename ScaleType>
    void serialize(Archive &archive, cv::Point_<ScaleType> &p) {
        archive(cereal::make_nvp("x", p.x), cereal::make_nvp("y", p.y));
    }
}

namespace ns_mv {
    static cv::Mat
    ConvertToVisibleMat(const cv::Mat &fImg, double maxScale = 1.0, double minScale = 1.0, bool color = true) {
        double min, max;
        cv::minMaxIdx(fImg, &min, &max);
        max *= maxScale;
        min *= minScale;
        cv::Mat adjMap;
        // v_new = (v_old-min) / (max - min) * 255
        // v_new = v_old * 255 / (max - min) - min * 255 / (max - min)
        fImg.convertTo(adjMap, CV_8UC1, 255 / (max - min), -min * 255 / (max - min));
        if (color) {
            cv::Mat falseColorsMap;
            cv::applyColorMap(adjMap, falseColorsMap, cv::ColormapTypes::COLORMAP_HOT);
            return falseColorsMap;
        } else {
            return adjMap;
        }

    }

    static void ShowImg(const cv::Mat &img, const std::string &winName = "win") {
        cv::namedWindow(winName, cv::WindowPropertyFlags::WND_PROP_ASPECT_RATIO);
        cv::imshow(winName, img);
        cv::waitKey(0);
    }
}


#endif //EXTRACTOR_UTILS_HPP
