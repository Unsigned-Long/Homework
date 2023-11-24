#ifndef INTERPOLATION_FUNCTION_SAMPLING_H
#define INTERPOLATION_FUNCTION_SAMPLING_H

#include "interpolation_points.h"
#include "functional"
#include "observation.h"

namespace ns_na {
    struct FunctionSampling {
    public:
        using Func = std::function<double(const double &)>;

    public:
        static Observations Sampling(const Func &func, double a, double b, int n, bool chebyshev);

    };
}


#endif //INTERPOLATION_FUNCTION_SAMPLING_H
