#ifndef INTEGRATION_SIMPSON_COMP_H
#define INTEGRATION_SIMPSON_COMP_H

#include "Eigen/Dense"

namespace ns_na {
    double SimpsonComp(const std::function<double(double)> &f, double a, double b, int n);
}


#endif //INTEGRATION_SIMPSON_COMP_H
