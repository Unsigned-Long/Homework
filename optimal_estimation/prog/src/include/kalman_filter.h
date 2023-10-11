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
#include "cereal/types/vector.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/utility.hpp"

namespace ns_kf {

    struct StateRecorder {
    public:
        std::vector<State> preStates;
        std::vector<State> estStates;
        std::vector<std::pair<double, double>> kxVec, kyVec, kvxVec, kvyVec;
    public:
        StateRecorder() = default;

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(
                    CEREAL_NVP(preStates), CEREAL_NVP(estStates),
                    CEREAL_NVP(kxVec), CEREAL_NVP(kyVec), CEREAL_NVP(kvxVec), CEREAL_NVP(kvyVec)
            );
        }
    };

    class KalmanFilter {
    public:
        using Ptr = std::shared_ptr<KalmanFilter>;

    private:
        State estState, preState;

        const double kx, ky;
        const double gravity;
        const double sigma_ex, sigma_ey, sigma_ex2, sigma_ey2;

        StateRecorder recorder;

    public:

        KalmanFilter(const State &initState, double kx, double ky,
                     double gravity, double sigmaEx, double sigmaEy);

        static Ptr Create(const State &initState, double kx, double ky,
                          double gravity, double sigmaEx, double sigmaEy);

        KalmanFilter &StatePredict(double t);

        KalmanFilter &MesUpdateSequentially1(const Measure &mes);

        KalmanFilter &MesUpdateSequentially2(const Measure &mes);

        KalmanFilter &MesUpdateGlobal(const Measure &mes);

        [[nodiscard]] const State &GetEstState() const;

        [[nodiscard]] const State &GetPreState() const;

        const StateRecorder &GetRecorder() const;

    protected:
        [[nodiscard]] Eigen::Matrix4d StateTransitionMat(const State &curState, double dt) const;

        [[nodiscard]] Eigen::Vector4d ControlInputVec(const State &curState, double dt) const;

        [[nodiscard]] Eigen::Matrix4d ErrorTransitionMat(const State &curState, double dt) const;

        static Measure MesPrediction(const State &curState);

        static Eigen::Matrix<double, 2, 4> MeasurementMat(const State &curState);
    };
}
#endif //PROG_KALMAN_FILTER_H
