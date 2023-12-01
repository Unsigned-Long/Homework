#include "gauss.h"

namespace ns_na {

    double Gauss(const std::function<double(double)> &f, double a, double b, int n) {
        double aCoeffs[6][6] = {
                {2.0},
                {1.0,       1.0},
                {5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0},
                {0.3478548, 0.6521452, 0.6521452, 0.3478548},
                {0.2369269, 0.4786287, 0.5688889, 0.4786287, 0.2369269},
                {0.1713245, 0.3607616, 0.4679139, 0.4679139, 0.3607616, 0.1713245}
        };
        double tCoeffs[6][6] = {
                {0.0},
                {-1.0 / std::sqrt(3.0), 1.0 / std::sqrt(3.0)},
                {-std::sqrt(3.0 / 5.0), 0.0,        std::sqrt(3.0 / 5.0)},
                {-0.8611363,            -0.3399810, 0.3399810,  0.8611363},
                {-0.9061798,            -0.5384693, 0.0,        0.5384693, 0.9061798},
                {-0.9324695,            -0.6612094, -0.2386192, 0.2386192, 0.6612094, 0.9324695}
        };
        auto x = [&a, &b](double t) {
            return (b - a) * 0.5 * t + (b + a) * 0.5;
        };
        if (n < 0 || n > 5) {
            throw std::runtime_error("unsupported order 'n'");
        } else {
            double res = 0.0;
            for (int i = 0; i < n; ++i) {
                res += aCoeffs[n - 1][i] * f(x(tCoeffs[n - 1][i]));
            }
            res *= (b - a) * 0.5;
            return res;
        }
    }
}