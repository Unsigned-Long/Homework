#include "simpson_comp.h"

namespace ns_na {

    double SimpsonComp(const std::function<double(double)> &f, double a, double b, int n) {
        double h = (b - a) / (2 * n);
        auto x = [&h, &a](int j) { return a + j * h; };
        double sum1 = 0.0, sum2 = 0.0;
        for (int j = 1; j <= n; ++j) {
            sum1 += f(x(2 * j - 1));
        }
        for (int j = 1; j <= n - 1; ++j) {
            sum2 += f(x(2 * j));
        }
        return h / 3.0 * (f(a) + 4 * sum1 + 2 * sum2 + f(b));
    }
}