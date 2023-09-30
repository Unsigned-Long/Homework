// Copyright (c) 2023. Created on 9/30/23 3:39 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef KALMAN_FILTER_MES_MANAGER_H
#define KALMAN_FILTER_MES_MANAGER_H

#include <ostream>
#include "utils.hpp"

namespace ns_kf {
    struct Measure {
    public:
        double timestamp;
        double range;
        double alpha;
        double sigma_r, sigma_a;

    public:
        Measure(double timestamp, double range, double alpha, double sigmaR, double sigmaA);

        friend std::ostream &operator<<(std::ostream &os, const Measure &manager);

        [[nodiscard]] Eigen::Vector2d MesVec() const;

        [[nodiscard]] Eigen::Matrix2d VarMat() const;

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(timestamp), CEREAL_NVP(range), CEREAL_NVP(alpha));
        }
    };
}

#endif //KALMAN_FILTER_MES_MANAGER_H
