// Copyright (c) 2023. Created on 9/30/23 3:40 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "measurement_manager.h"

namespace ns_kf {


    Eigen::Vector2d MesManager::MesVec() const {
        Eigen::Vector2d v;
        v(0) = range;
        v(1) = alpha;
        return v;
    }

    MesManager::MesManager(double timestamp, double range, double alpha, double sigmaR, double sigmaA) : timestamp(
            timestamp), range(range), alpha(alpha), sigma_r(sigmaR), sigma_a(sigmaA) {}

    std::ostream &operator<<(std::ostream &os, const MesManager &manager) {
        os << "timestamp: " << manager.timestamp << " range: " << manager.range << " alpha: " << manager.alpha
           << " sigma_r: " << manager.sigma_r << " sigma_a: " << manager.sigma_a;
        return os;
    }

    Eigen::Matrix2d MesManager::VarMat() const {
        Eigen::Matrix2d var = Eigen::Matrix2d::Zero();
        var(0, 0) = sigma_r * sigma_r;
        var(1, 1) = sigma_a * sigma_a;
        return var;
    }
}