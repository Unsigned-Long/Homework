#ifndef INTERPOLATION_INTERPOLATION_POINTS_H
#define INTERPOLATION_INTERPOLATION_POINTS_H

#include "vector"
#include "cmath"

namespace ns_na {
    std::vector<double> ChebyshevPoints(double a, double b, int n);

    std::vector<double> AveragePoints(double a, double b, int n);

}

#endif //INTERPOLATION_INTERPOLATION_POINTS_H
