#ifndef INTEGRATION_TRAPEZOIDAL_COMP_H
#define INTEGRATION_TRAPEZOIDAL_COMP_H

#include "Eigen/Dense"
#include "functional"

namespace ns_na {
    double TrapezoidalComp(const std::function<double(double)> &f, double a, double b, int n);
}

#endif //INTEGRATION_TRAPEZOIDAL_COMP_H
