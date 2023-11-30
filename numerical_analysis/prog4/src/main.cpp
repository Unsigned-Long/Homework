#include "trapezoidal_comp.h"
#include "simpson_comp.h"
#include "romberg.h"
#include "gauss.h"
#include "artwork/logger/logger.h"

int main() {
    ns_log::ns_priv::stdLogger.setPrecision(10);

    // std::function<double(double)> f = [](double x) { if (x == 0.0)return 1.0; else return std::sin(x) / x; };
    std::function<double(double)> f = [](double x) { return 1.0 / (1.0 + x * x); };
    double res1 = ns_na::TrapezoidalComp(f, -5.0, 5.0, 8);
    LOG_VAR(res1)
    // double res2 = ns_na::SimpsonComp(f, 0.0, 1.0, 8);
    // LOG_VAR(res2)
    // double res3 = ns_na::Romberg(f, 0.0, 1.0, 3);
    // LOG_VAR(res3)
    // double res4 = ns_na::Gauss(f, 0.0, 1.0, 2);
    // LOG_VAR(res4)
    // double res5 = ns_na::Gauss(f, 0.0, 1.0, 3);
    // LOG_VAR(res5)
    return 0;
}


