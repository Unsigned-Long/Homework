#include "function_sampling.h"

namespace ns_na {

    Observations
    FunctionSampling::Sampling(const FunctionSampling::Func &func, double a, double b, int n, bool chebyshev) {
        Observations observations(n);
        std::vector<double> points;
        if (chebyshev) {
            points = ChebyshevPoints(a, b, n);
        } else {
            points = AveragePoints(a, b, n);
        }
        for (int i = 0; i < n; ++i) {
            observations.at(i).x = points.at(i);
            observations.at(i).y = func(points.at(i));
        }
        return observations;
    }
}