#include "lagrange.h"
#include "interpolation_points.h"
#include "function_sampling.h"

const int samples = 30;

void TestLagrange() {
    ns_na::Observations observations;
    observations.emplace_back(1.0, 0.7);
    observations.emplace_back(2.0, 1.1);
    observations.emplace_back(3.0, 1.4);

    auto lagrange = ns_na::LagrangeInterpolation(observations);
    LOG_VAR(lagrange(2.5))
}

void TestChebyshevPoints() {
    auto points = ns_na::ChebyshevPoints(-1, 1, 10);
    LOG_VAR(points)
}

void TestSampling() {
    auto obsVec1 = ns_na::FunctionSampling::Sampling([](const double &x) {
        return 1.0 / (1.0 + x * x);
    }, -5.0, 5.0, 10, true);
    LOG_VAR(obsVec1)

    auto obsVec2 = ns_na::FunctionSampling::Sampling([](const double &x) {
        return 1.0 / (1.0 + x * x);
    }, -5.0, 5.0, 10, false);
    LOG_VAR(obsVec2)
}

void Integration(const std::string &rootPath, const ns_na::FunctionSampling::Func &func, double a, double b) {
    auto testPoints = ns_na::AveragePoints(a, b, 1E4);
    ns_na::Observation::SaveObservationsToDisk(
            rootPath + "/truth.txt", ns_na::FunctionSampling::Sampling(func, a, b, 1E4, false)
    );
    {
        // chebyshev
        auto lagChebyshevSamples = ns_na::FunctionSampling::Sampling(func, a, b, samples, true);
        ns_na::Observation::SaveObservationsToDisk(
                rootPath + "/lagChebyshevSamples.txt", lagChebyshevSamples
        );

        auto lagChebyshev = ns_na::LagrangeInterpolation(lagChebyshevSamples);

        auto lagChebyshevResults = lagChebyshev(testPoints);
        ns_na::Observation::SaveObservationsToDisk(
                rootPath + "/lagChebyshevResults.txt", lagChebyshevResults
        );
    }
    {
        // average
        auto lagAvgSamples = ns_na::FunctionSampling::Sampling(func, a, b, samples, false);
        ns_na::Observation::SaveObservationsToDisk(
                rootPath + "/lagAvgSamples.txt", lagAvgSamples
        );

        auto lagAvg = ns_na::LagrangeInterpolation(lagAvgSamples);

        auto lagAvgResults = lagAvg(testPoints);
        ns_na::Observation::SaveObservationsToDisk(
                rootPath + "/lagAvgResults.txt", lagAvgResults
        );
    }
}

int main() {
    // TestLagrange();
    // TestChebyshevPoints();
    // TestSampling();
    Integration("/home/csl/Homework/numerical_analysis/prog3/data/rongo", [](const double &x) {
        return 1.0 / (1.0 + x * x);
    }, -5.0, 5.0);
    Integration("/home/csl/Homework/numerical_analysis/prog3/data/sinx", [](const double &x) {
        return std::sin(x);
    }, -5.0, 5.0);
    Integration("/home/csl/Homework/numerical_analysis/prog3/data/ex", [](const double &x) {
        return std::exp(x);
    }, -5.0, 5.0);
    Integration("/home/csl/Homework/numerical_analysis/prog3/data/ln", [](const double &x) {
        return std::log(1.0 + x * x);
    }, -5.0, 5.0);
    Integration("/home/csl/Homework/numerical_analysis/prog3/data/abs", [](const double &x) {
        return std::abs(x);
    }, -5.0, 5.0);
    return 0;
}


