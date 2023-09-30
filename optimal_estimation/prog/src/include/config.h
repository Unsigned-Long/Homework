// Copyright (c) 2023. Created on 9/30/23 4:39 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef KALMAN_FILTER_CONFIG_H
#define KALMAN_FILTER_CONFIG_H

#include <ostream>
#include "utils.hpp"
#include "cereal/archives/xml.hpp"
#include "fstream"
#include "state_manager.h"

namespace ns_kf {
    enum class SolveMode {
        GLOBAL_EKF,
        LOCAL_EKF_1,
        LOCAL_EKF_2
    };

    struct Config {
    public:
        std::string data_path;
        std::string output_path;
        SolveMode mode;
        double kx{}, ky{};
        double gravity{};
        double sigma_ex{}, sigma_ey{};
        StateManager init_state{};

    public:
        Config();

        void Save(const std::string &filename);

        static Config Load(const std::string &filename);

        friend std::ostream &operator<<(std::ostream &os, const Config &config);

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(
                    CEREAL_NVP(data_path), CEREAL_NVP(output_path),
                    CEREAL_NVP(mode),
                    CEREAL_NVP(kx), CEREAL_NVP(ky),
                    CEREAL_NVP(gravity),
                    CEREAL_NVP(sigma_ex), CEREAL_NVP(sigma_ey), CEREAL_NVP(init_state)
            );
        }
    };
}


#endif //KALMAN_FILTER_CONFIG_H
