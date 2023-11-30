#include "romberg.h"

namespace ns_na {

    double Romberg(const std::function<double(double)> &f, double a, double b, int m) {
        Eigen::MatrixXd T(m + 1, m + 1);
        T.setZero();
        T(0, 0) = (b - a) * 0.5 * (f(a) + f(b));
        for (int k = 1; k <= m; ++k) {
            double sum = 0.0;
            for (int i = 1; i <= std::pow(2, k - 1); ++i) {
                sum += f(a + (2 * i - 1) * (b - a) / std::pow(2, k));
            }
            T(k, 0) = 0.5 * T(k - 1, 0) + (b - a) / std::pow(2, k) * sum;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                T(j, i) = (std::pow(4, i) * T(j, i - 1) - T(j - 1, i - 1)) / (std::pow(4, i) - 1);
            }
        }
        return T(m, m);
    }
}