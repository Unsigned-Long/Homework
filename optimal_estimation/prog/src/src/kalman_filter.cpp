// Copyright (c) 2023. Created on 9/30/23 2:44 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "kalman_filter.h"

#include <utility>
#include "utility"

namespace ns_kf {

    // ------------
    // KalmanFilter
    // ------------
    Eigen::Matrix4d KalmanFilter::StateTransitionMat(const State &curState, double dt) const {
        Eigen::Matrix4d phiMat = Eigen::Matrix4d::Identity();
        phiMat(0, 2) = dt;
        phiMat(1, 3) = dt;
        phiMat(2, 2) = 1 - 2.0 * kx * curState.Vx() * dt;
        phiMat(3, 3) = 1 + 2.0 * ky * curState.Vy() * dt;
        return phiMat;
    }

    Eigen::Vector4d KalmanFilter::ControlInputVec(const State &curState, double dt) const {
        double dt2 = dt * dt;
        Eigen::Matrix4d m = Eigen::Matrix4d::Zero();
        m(0, 0) = dt;
        m(1, 1) = dt;
        m(2, 2) = dt - kx * curState.Vx() * dt2;
        m(3, 3) = dt + ky * curState.Vy() * dt2;
        m(0, 2) = dt2 * 0.5;
        m(1, 3) = dt2 * 0.5;
        Eigen::Vector4d v = Eigen::Vector4d::Zero();
        v(2) = kx * curState.Vx() * curState.Vx();
        v(3) = -ky * curState.Vy() * curState.Vy() - gravity;
        Eigen::Vector4d cVec = m * v;
        return cVec;
    }

    Eigen::Matrix4d KalmanFilter::ErrorTransitionMat(const State &curState, double dt) const {
        const double dt2 = dt * dt, dt3 = dt2 * dt;
        Eigen::Matrix4d m = Eigen::Matrix4d::Zero();
        m(0, 0) = dt3 / 3.0 * sigma_ex2;
        m(1, 1) = dt3 / 3.0 * sigma_ey2;
        m(2, 2) = (dt - 2.0 * kx * curState.Vx() * dt2 + 4.0 / 3.0 * kx * kx * curState.Vx() * curState.Vx() * dt3)
                  * sigma_ex2;
        m(3, 3) = (dt + 2.0 * ky * curState.Vy() * dt2 + 4.0 / 3.0 * ky * ky * curState.Vy() * curState.Vy() * dt3)
                  * sigma_ey2;
        m(0, 2) = m(2, 0) = (0.5 * dt2 - 2.0 / 3.0 * kx * curState.Vx() * dt3) * sigma_ex2;
        m(1, 3) = m(3, 1) = (0.5 * dt2 + 2.0 / 3.0 * ky * curState.Vy() * dt3) * sigma_ey2;
        return m;
    }

    KalmanFilter &KalmanFilter::StatePredict(double t) {
        // state transition
        Eigen::Matrix4d phiMat = StateTransitionMat(estState, t - estState.timestamp);
        Eigen::Vector4d conVec = ControlInputVec(estState, t - estState.timestamp);
        preState.state = phiMat * estState.state + conVec;

        // variance propagation
        Eigen::Matrix4d errorMat = ErrorTransitionMat(estState, t - estState.timestamp);
        preState.var = phiMat * estState.var * phiMat.transpose() + errorMat;
        return *this;
    }

    Measure KalmanFilter::MesPrediction(const State &curState) {
        double range = std::sqrt(curState.Px() * curState.Py() + curState.Py() * curState.Py());
        double alpha = std::atan(curState.Px() / curState.Py());
        return {curState.timestamp, range, alpha, 0.0, 0.0};
    }

    Eigen::Matrix<double, 2, 4> KalmanFilter::MeasurementMat(const State &curState) {
        Eigen::Matrix<double, 2, 4> m = Eigen::Matrix<double, 2, 4>::Zero();
        m(0, 0) = curState.Px() / std::sqrt(curState.Px() * curState.Py() + curState.Py() * curState.Py());
        m(0, 1) = curState.Py() / std::sqrt(curState.Px() * curState.Py() + curState.Py() * curState.Py());
        m(1, 0) = 1.0 / (1.0 + std::pow(curState.Px() / curState.Py(), 2.0)) / curState.Py();
        m(1, 1) = 1.0 / (1.0 + std::pow(curState.Px() / curState.Py(), 2.0)) * (-curState.Px()) /
                  (curState.Py() * curState.Py());
        return m;
    }

    KalmanFilter &KalmanFilter::MesUpdateSequentially1(const Measure &mes) {
        // update based on range measurement
        {
            double v1 = mes.range - MesPrediction(preState).range;
            Eigen::Matrix<double, 1, 4> h1 = MeasurementMat(preState).row(0);
            Eigen::Vector4d k1 = preState.var * h1.transpose()
                                 / ((h1 * preState.var * h1.transpose())(0, 0) + mes.sigma_r * mes.sigma_r);
            preState.state = preState.state + k1 * v1;
            preState.var = (Eigen::Matrix4d::Identity() - k1 * h1) * preState.var;
        }
        // update based on alpha measurement
        {
            double v2 = mes.alpha - MesPrediction(preState).alpha;
            Eigen::Matrix<double, 1, 4> h2 = MeasurementMat(preState).row(1);
            Eigen::Vector4d k2 = preState.var * h2.transpose()
                                 / ((h2 * preState.var * h2.transpose())(0, 0) + mes.sigma_a * mes.sigma_a);
            preState.state = preState.state + k2 * v2;
            preState.var = (Eigen::Matrix4d::Identity() - k2 * h2) * preState.var;
        }
        estState = preState;
        return *this;
    }


    KalmanFilter &KalmanFilter::MesUpdateSequentially2(const Measure &mes) {
        // update based on alpha measurement
        {
            double v2 = mes.alpha - MesPrediction(preState).alpha;
            Eigen::Matrix<double, 1, 4> h2 = MeasurementMat(preState).row(1);
            Eigen::Vector4d k2 = preState.var * h2.transpose()
                                 / ((h2 * preState.var * h2.transpose())(0, 0) + mes.sigma_a * mes.sigma_a);
            preState.state = preState.state + k2 * v2;
            preState.var = (Eigen::Matrix4d::Identity() - k2 * h2) * preState.var;
        }
        // update based on range measurement
        {
            double v1 = mes.range - MesPrediction(preState).range;
            Eigen::Matrix<double, 1, 4> h1 = MeasurementMat(preState).row(0);
            Eigen::Vector4d k1 = preState.var * h1.transpose()
                                 / ((h1 * preState.var * h1.transpose())(0, 0) + mes.sigma_r * mes.sigma_r);
            preState.state = preState.state + k1 * v1;
            preState.var = (Eigen::Matrix4d::Identity() - k1 * h1) * preState.var;
        }
        estState = preState;
        return *this;
        return *this;
    }


    KalmanFilter &KalmanFilter::MesUpdateGlobal(const Measure &mes) {
        Eigen::Vector2d v = mes.MesVec() - MesPrediction(preState).MesVec();
        Eigen::Matrix<double, 2, 4> h = MeasurementMat(preState);
        Eigen::Matrix<double, 4, 2> k = preState.var * h.transpose() *
                                        (h * preState.var * h.transpose() + mes.VarMat()).inverse();
        estState.state = preState.state + k * v;
        estState.var = (Eigen::Matrix4d::Identity() - k * h) * preState.var;
        return *this;
    }

    KalmanFilter::KalmanFilter(const State &initState, const double kx, const double ky, const double gravity,
                               const double sigmaEx, const double sigmaEy)
            : estState(initState), preState(initState), kx(kx), ky(ky),
              gravity(gravity), sigma_ex(sigmaEx), sigma_ey(sigmaEy),
              sigma_ex2(sigma_ex * sigma_ex), sigma_ey2(sigma_ey * sigma_ey) {}

    KalmanFilter::Ptr
    KalmanFilter::Create(const State &initState, double kx, double ky, double gravity, double sigmaEx,
                         double sigmaEy) {
        return std::make_shared<KalmanFilter>(initState, kx, ky, gravity, sigmaEx, sigmaEy);
    }

    const State &KalmanFilter::GetEstState() const {
        return estState;
    }

    const State &KalmanFilter::GetPreState() const {
        return preState;
    }
}