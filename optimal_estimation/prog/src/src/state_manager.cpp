// Copyright (c) 2023. Created on 9/30/23 3:38 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "state_manager.h"

namespace ns_kf {

    // ------------
    // State
    // ------------
    double &State::Px() { return state(0); }

    double &State::Py() { return state(1); }

    double &State::Vx() { return state(2); }

    double &State::Vy() { return state(3); }


    std::ostream &operator<<(std::ostream &os, const State &manager) {
        os << "'t': " << manager.timestamp
           << ", 'state': " << manager.state.transpose()
           << ", 'var': \n" << manager.var;
        return os;
    }

    const double &State::Px() const { return state(0); }

    const double &State::Py() const { return state(1); }

    const double &State::Vx() const { return state(2); }

    const double &State::Vy() const { return state(3); }

    State::State(double timestamp, Eigen::Vector4d state, Eigen::Matrix4d var)
            : timestamp(timestamp), state(std::move(state)), var(std::move(var)) {}

    State::State() : timestamp(0.0), state(Eigen::Vector4d::Zero()), var(Eigen::Matrix4d::Identity()) {}

}