#include "interpolation_points.h"

namespace ns_na {

    std::vector<double> ChebyshevPoints(double a, double b, int n) {
        double v1 = (a + b) * 0.5, v2 = (b - a) * 0.5;
        std::vector<double> points(n);
        for (int i = 1; i <= n; ++i) {
            points.at(i - 1) = v1 + v2 * std::cos((2.0 * i - 1) * M_PI / (2.0 * n));
        }
        return points;
    }

    std::vector<double> AveragePoints(double a, double b, int n) {
        std::vector<double> points(n);
        double delta = (b - a) / (n - 1);
        double v = a;
        for (int i = 0; i < n; ++i) {
            points.at(i) = v;
            v += delta;
        }
        return points;
    }
}