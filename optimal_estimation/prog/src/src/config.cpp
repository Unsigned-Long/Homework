// Copyright (c) 2023. Created on 9/30/23 4:40 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "config.h"

namespace ns_kf {

    Config Config::Load(const std::string &filename) {
        Config config;
        std::ifstream file(filename);
        auto ar = cereal::XMLInputArchive(file);
        ar(cereal::make_nvp("config", config));
        return config;
    }

    void Config::Save(const std::string &filename) {
        std::ofstream file(filename);
        auto ar = cereal::XMLOutputArchive(file);
        ar(cereal::make_nvp("config", *this));
    }

    std::ostream &operator<<(std::ostream &os, const Config &config) {
        os << "  'data_path': " << config.data_path
           << "\n'output_path': " << config.output_path
           << "\n'mode': " << static_cast<int>(config.mode)
           << "\n'kx': " << config.kx << ", 'ky': " << config.ky << ", 'gravity': " << config.gravity
           << "\n'sigma_ex': " << config.sigma_ex << ", 'sigma_ey': " << config.sigma_ey
           << "\n'init_state': " << config.init_state;
        return os;
    }


    Config::Config() = default;
}