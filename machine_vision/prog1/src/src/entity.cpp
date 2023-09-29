// Copyright (c) 2023. Created on 9/29/23 10:18 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "entity.h"
#include <utility>

namespace ns_mv {

    std::string Corner::Type() {
        return "Corner";
    }

    Corner::Corner(Eigen::Vector2f pos) : p(std::move(pos)) {}

    float Corner::GetY() const { return p(1); }

    float Corner::GetX() const { return p(0); }

    std::ostream &operator<<(std::ostream &os, const Corner &corner) {
        os << "'x': " << corner.GetX() << ", 'y': " << corner.GetY();
        return os;
    }

    Line::Line(Eigen::Vector2f p1, Eigen::Vector2f p2) : p1(std::move(p1)), p2(std::move(p2)) {}

    std::string Line::Type() {
        return "Line";
    }

    std::ostream &operator<<(std::ostream &os, const Line &line) {
        os << "'x1': " << line.p1(0) << ", 'y1': " << line.p1(1)
           << "'x2': " << line.p2(0) << ", 'y2': " << line.p2(1);
        return os;
    }
}