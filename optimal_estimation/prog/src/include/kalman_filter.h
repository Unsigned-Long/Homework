// Copyright (c) 2023. Created on 9/30/23 2:44 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef PROG_KALMAN_FILTER_H
#define PROG_KALMAN_FILTER_H

#include <utility>
#include <ostream>
#include "state_manager.h"
#include "mes_manager.h"

namespace ns_kf {


    class KalmanFilter {
    public:
        using Ptr = std::shared_ptr<KalmanFilter>;

    private:
        StateManager estState, preState;

        const double kx, ky;
        const double gravity;
        const double sigma_ex, sigma_ey, sigma_ex2, sigma_ey2;

    public:

        KalmanFilter(const StateManager &initState, double kx, double ky,
                     double gravity, double sigmaEx, double sigmaEy);

        static Ptr Create(const StateManager &initState, double kx, double ky,
                          double gravity, double sigmaEx, double sigmaEy);

        KalmanFilter &StateTransition(double t);

        KalmanFilter &MesUpdateSequentially1(const MesManager &mes);

        KalmanFilter &MesUpdateSequentially2(const MesManager &mes);

        KalmanFilter &MesUpdateGlobal(const MesManager &mes);

        const StateManager &GetEstState() const;

    protected:
        [[nodiscard]] Eigen::Matrix4d StateTransitionMat(const StateManager &curState, double dt) const;

        [[nodiscard]] Eigen::Vector4d ControlInputVec(const StateManager &curState, double dt) const;

        [[nodiscard]] Eigen::Matrix4d ErrorTransitionMat(const StateManager &curState, double dt) const;

        static MesManager MesPrediction(const StateManager &curState);

        static Eigen::Matrix<double, 2, 4> MeasurementMat(const StateManager &curState);
    };
}
#endif //PROG_KALMAN_FILTER_H
