// Copyright (c) 2023. Created on 9/30/23 2:44 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef KALMAN_FILTER_UTILS_HPP
#define KALMAN_FILTER_UTILS_HPP

#include "Eigen/Dense"
#include "cereal/cereal.hpp"

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

    template<class Archive, typename ScaleType>
    void serialize(Archive &archive, Eigen::Quaternion<ScaleType> &q) {
        archive(
                cereal::make_nvp("qx", q.coeffs()[0]),
                cereal::make_nvp("qy", q.coeffs()[1]),
                cereal::make_nvp("qz", q.coeffs()[2]),
                cereal::make_nvp("qw", q.coeffs()[3])
        );
    }
}

namespace ns_kf {

}

#endif //KALMAN_FILTER_UTILS_HPP
