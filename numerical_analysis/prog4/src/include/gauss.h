#ifndef INTEGRATION_GAUSS_H
#define INTEGRATION_GAUSS_H

#include "Eigen/Dense"

namespace ns_na {
    double Gauss(const std::function<double(double)> &f, double a, double b, int n);

}


#endif //INTEGRATION_GAUSS_H
