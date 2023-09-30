// Copyright (c) 2023. Created on 9/30/23 3:38 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef KALMAN_FILTER_STATE_MANAGER_H
#define KALMAN_FILTER_STATE_MANAGER_H

#include "utils.hpp"

namespace ns_kf {
    struct State {
    public:
        double timestamp{};

        // px, py, vx, vy
        Eigen::Vector4d state;
        /**
         * pxpx pxpy pxvx pxvy
         * pypx pypy pyvx pyvy
         * vxpx vxpy vxvx vxvy
         * vypx vypy vyvx vyvy
         */
        Eigen::Matrix4d var;

    public:
        State(double timestamp, Eigen::Vector4d state, Eigen::Matrix4d var);

        State();

        double &Px();

        double &Py();

        double &Vx();

        double &Vy();

        [[nodiscard]] const double &Px() const;

        [[nodiscard]] const double &Py() const;

        [[nodiscard]] const double &Vx() const;

        [[nodiscard]] const double &Vy() const;

        friend std::ostream &operator<<(std::ostream &os, const State &manager);

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(timestamp), CEREAL_NVP(state), CEREAL_NVP(var));
        }

    };
}

#endif //KALMAN_FILTER_STATE_MANAGER_H
