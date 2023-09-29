// Copyright (c) 2023. Created on 9/29/23 10:16 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "extractor.h"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace ns_mv {

    Extractor::Extractor() = default;

    std::vector<Entity::Ptr> CornerExtractor::Process(cv::Mat img) {
        std::vector<Entity::Ptr> corners;
        switch (type) {
            case ExtractorType::HARRIS: {
                // convert to gray image
                cv::Mat gImg;
                cv::cvtColor(img, gImg, cv::COLOR_BGR2GRAY);
                // perform harris corner detect
                cv::Mat dstImg;
                cv::cornerHarris(gImg, dstImg, 3, 3, 0.04);
                // show the dst image
                ns_mv::ShowImg(ns_mv::ConvertToVisibleMat(dstImg));
            }
                break;
            case ExtractorType::SIFT: {

            }
                break;
            case ExtractorType::SURF: {

            }
                break;
            case ExtractorType::ORB: {

            }
                break;
            case ExtractorType::FAST: {

            }
                break;
        }
        return corners;
    }

    CornerExtractor::Ptr CornerExtractor::Create(CornerExtractor::ExtractorType type) {
        return std::make_shared<CornerExtractor>(type);
    }

    CornerExtractor::CornerExtractor(CornerExtractor::ExtractorType type) : type(type) {}

    LineExtractor::LineExtractor() = default;

    std::vector<Entity::Ptr> LineExtractor::Process(cv::Mat img) {
        std::vector<Entity::Ptr> lines;
        return lines;
    }

    LineExtractor::Ptr LineExtractor::Create() {
        return std::make_shared<LineExtractor>();
    }
}