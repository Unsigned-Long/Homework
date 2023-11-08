#ifndef INTERPOLATION_LAGRANGE_H
#define INTERPOLATION_LAGRANGE_H

#include "observation.h"

#define FORMAT_VECTOR

#include "artwork/logger/logger.h"

namespace ns_na {
    class LagrangeInterpolation {
    private:
        Observations obsVec;
        std::vector<double> omegas;

    public:
        explicit LagrangeInterpolation(const Observations &observations);

        Observation operator()(double x) const;

        Observations operator()(const std::vector<double> &xVec) const;
    };
}


#endif //INTERPOLATION_LAGRANGE_H
