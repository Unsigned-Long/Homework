// Copyright (c) 2023. Created on 9/29/23 10:18 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "entity.h"
#include <utility>

namespace ns_mv {
    pangolin::ColourWheel Entity::WHEEL = pangolin::ColourWheel(1.0);

    std::string Corner::Type() {
        return "Corner";
    }

    Corner::Corner(cv::Point2f pos) : p(std::move(pos)) {}

    std::ostream &operator<<(std::ostream &os, const Corner &corner) {
        os << "'x': " << corner.p.x << ", 'y': " << corner.p.y;
        return os;
    }

    Corner::Ptr Corner::Create(const cv::Point2f &pos) {
        return std::make_shared<Corner>(pos);
    }

    void Corner::Draw(const cv::Mat &img) {
        auto color = WHEEL.GetUniqueColour();
        cv::drawMarker(
                img, p, cv::Scalar(color.b * 255.0, color.g * 255.0, color.r * 255.0),
                cv::MarkerTypes::MARKER_TILTED_CROSS, 10, 2
        );
    }

    Line::Line(cv::Point2f p1, cv::Point2f p2) : p1(std::move(p1)), p2(std::move(p2)) {}

    std::string Line::Type() {
        return "Line";
    }

    std::ostream &operator<<(std::ostream &os, const Line &line) {
        os << "'x1': " << line.p1.x << ", 'y1': " << line.p1.y
           << "'x2': " << line.p2.x << ", 'y2': " << line.p2.y;
        return os;
    }

    Line::Ptr Line::Create(const cv::Point2f &p1, const cv::Point2f &p2) {
        return std::make_shared<Line>(p1, p2);
    }

    void Line::Draw(const cv::Mat &img) {

    }
}