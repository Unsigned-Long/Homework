#include "lagrange.h"

namespace ns_na {

    ns_na::LagrangeInterpolation::LagrangeInterpolation(const std::vector<Observation> &observations)
            : obsVec(observations), omegas(observations.size()) {
        for (int i = 0; i < static_cast<int>(obsVec.size()); ++i) {
            double omegaInv = 1.0;
            for (int k = 0; k < static_cast<int>(obsVec.size()); ++k) {
                if (k == i) { continue; }
                omegaInv *= obsVec.at(i).x - obsVec.at(k).x;
            }
            omegas.at(i) = 1.0 / omegaInv;
        }
        // LOG_VAR(omegas)
    }

    Observation LagrangeInterpolation::operator()(double x) const {
        for (const auto &obv: obsVec) { if (std::abs(x - obv.x) < 1E-10) { return obv; }}
        double v1 = 0.0, v2 = 0.0;
        for (int i = 0; i < static_cast<int>(obsVec.size()); ++i) {
            double v3 = omegas.at(i) / (x - obsVec.at(i).x);
            v1 += v3 * obsVec.at(i).y;
            v2 += v3;
        }
        return {x, v1 / v2};
    }

    Observations LagrangeInterpolation::operator()(const std::vector<double> &xVec) const {
        Observations resVec(xVec.size());
        for (int i = 0; i < static_cast<int>(xVec.size()); ++i) {
            resVec.at(i) = this->operator()(xVec.at(i));
        }
        return resVec;
    }
}