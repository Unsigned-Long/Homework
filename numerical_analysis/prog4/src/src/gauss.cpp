#include "gauss.h"

namespace ns_na {

    double Gauss(const std::function<double(double)> &f, double a, double b, int n) {
        auto x = [&a, &b](double t) {
            return (b - a) * 0.5 * t + (b + a) * 0.5;
        };
        if (n == 2) {
            double v1 = 1.0 * f(x(-1.0 / std::sqrt(3.0))) + 1.0 * f(x(1.0 / std::sqrt(3.0)));
            return (b - a) * 0.5 * v1;
        } else if (n == 3) {
            double v1 = 5.0 / 9.0 * f(x(-std::sqrt(3.0 / 5.0))) + 8.0 / 9.0 * f(x(0.0))
                        + 5.0 / 9.0 * f(x(std::sqrt(3.0 / 5.0)));
            return (b - a) * 0.5 * v1;
        } else {
            throw std::runtime_error("unsupported order 'n'");
        }
    }
}