// Copyright (c) 2023. Created on 9/30/23 3:38 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "state_manager.h"

namespace ns_kf {

    // ------------
    // StateManager
    // ------------
    double &StateManager::Px() { return state(0); }

    double &StateManager::Py() { return state(1); }

    double &StateManager::Vx() { return state(2); }

    double &StateManager::Vy() { return state(3); }


    std::ostream &operator<<(std::ostream &os, const StateManager &manager) {
        os << "'t': " << manager.timestamp
           << ", 'state': " << manager.state.transpose()
           << ", 'var': \n" << manager.var;
        return os;
    }

    const double &StateManager::Px() const { return state(0); }

    const double &StateManager::Py() const { return state(1); }

    const double &StateManager::Vx() const { return state(2); }

    const double &StateManager::Vy() const { return state(3); }

    StateManager::StateManager(double timestamp, Eigen::Vector4d state, Eigen::Matrix4d var)
            : timestamp(timestamp), state(std::move(state)), var(std::move(var)) {}

    StateManager::StateManager() : timestamp(0.0), state(Eigen::Vector4d::Zero()), var(Eigen::Matrix4d::Identity()) {}

}