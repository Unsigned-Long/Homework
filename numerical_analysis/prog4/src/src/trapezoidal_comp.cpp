#include "trapezoidal_comp.h"

namespace ns_na {

    double TrapezoidalComp(const std::function<double(double)> &f, double a, double b, int n) {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 1; i <= n - 1; ++i) { sum += f(a + i * h); }
        return h * 0.5 * (f(a) + 2.0 * sum + f(b));
    }
}