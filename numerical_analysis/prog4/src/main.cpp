#include "trapezoidal_comp.h"
#include "simpson_comp.h"
#include "romberg.h"
#include "gauss.h"
#include "fstream"
#include "iomanip"
#include "iostream"

void func1() {
    std::function<double(double)> f = [](double x) { return 1.0 / (1.0 + x * x); };
    constexpr double a = -2.0, b = 2.0;
    {
        for (int n = 2; n < 6; ++n) {
            std::cout << std::fixed << std::setprecision(20) << ns_na::Gauss(f, a, b, n) << std::endl;
            std::cout << std::fixed << std::setprecision(20) << ns_na::Gauss(f, a, b, n) - std::atan(2.0) * 2
                      << std::endl;
        }
        return;
    }
    std::ofstream trap("/home/csl/Homework/numerical_analysis/prog4/data/runge/trap.txt");
    std::ofstream simpson("/home/csl/Homework/numerical_analysis/prog4/data/runge/simpson.txt");
    std::ofstream romberg("/home/csl/Homework/numerical_analysis/prog4/data/runge/romberg.txt");
    trap << std::fixed << std::setprecision(20);
    simpson << std::fixed << std::setprecision(20);
    romberg << std::fixed << std::setprecision(20);
    for (int n = 1; n < 10; ++n) {
        std::cout << n << std::endl;
        double res1 = ns_na::TrapezoidalComp(f, a, b, n);
        trap << n << ',' << res1 << std::endl;
        double res2 = ns_na::SimpsonComp(f, a, b, n);
        simpson << n << ',' << res2 << std::endl;
        double res3 = ns_na::Romberg(f, a, b, n);
        romberg << n << ',' << res3 << std::endl;
    }
}

void func2() {
    std::function<double(double)> f = [](double x) { return 0.1 * x * x * sin(M_PI * x) * sin(M_PI * x); };
    constexpr double a = 0.0, b = 10.0;
    {
        for (int n = 2; n < 6; ++n) {
            std::cout << std::fixed << std::setprecision(20) << ns_na::Gauss(f, a, b, n) << std::endl;
        }

        return;
    }
    std::ofstream trap("/home/csl/Homework/numerical_analysis/prog4/data/zigzag/trap.txt");
    std::ofstream simpson("/home/csl/Homework/numerical_analysis/prog4/data/zigzag/simpson.txt");
    std::ofstream romberg("/home/csl/Homework/numerical_analysis/prog4/data/zigzag/romberg.txt");
    trap << std::fixed << std::setprecision(20);
    simpson << std::fixed << std::setprecision(20);
    romberg << std::fixed << std::setprecision(20);
    for (int n = 1; n < 10; ++n) {
        std::cout << n << std::endl;
        double res1 = ns_na::TrapezoidalComp(f, a, b, n);
        trap << n << ',' << res1 << std::endl;
        double res2 = ns_na::SimpsonComp(f, a, b, n);
        simpson << n << ',' << res2 << std::endl;
        double res3 = ns_na::Romberg(f, a, b, n);
        romberg << n << ',' << res3 << std::endl;
    }
}

int main() {
    func2();
    // std::function<double(double)> f = [](double x) { if (x == 0.0)return 1.0; else return std::sin(x) / x; };
    // std::cout << std::fixed << std::setprecision(20);
    // double res4 = ns_na::Gauss(f, 0.0, 1.0, 2);
    // std::cout << res4 << std::endl;
    // double res5 = ns_na::Gauss(f, 0.0, 1.0, 3);
    // std::cout << res5 << std::endl;

    return 0;
}


