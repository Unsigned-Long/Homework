#ifndef INTEGRATION_ROMBERG_H
#define INTEGRATION_ROMBERG_H

#include "Eigen/Dense"

namespace ns_na {
    double Romberg(const std::function<double(double)> &f, double a, double b, int m);

}


#endif //INTEGRATION_ROMBERG_H
