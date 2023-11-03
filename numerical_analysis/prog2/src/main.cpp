#include "lasso.h"
#include "Eigen/Dense"
#include "artwork/logger/logger.h"
#include "sampling.hpp"

namespace ns_LASSO {
    constexpr static int M = 512;
    constexpr static int N = 1024;

    constexpr static double MU = 1E-3;

    constexpr static int NON_ZERO = 50;

    constexpr static double HUBER_DELTA = 1E-5;

    constexpr static double ALPHA = 1E-1;

    constexpr static double FUNC_THD = 1E-8;

    constexpr static double GRAD_THD = 1E-8;
}

void LASSOSolver() {
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());

    // generate matrix A
    Eigen::MatrixXd AMat = Eigen::MatrixXd::Random(ns_LASSO::M, ns_LASSO::N);
    // LOG_VAR(AMat)

    // generate vector x
    Eigen::VectorXd xVec = Eigen::VectorXd(ns_LASSO::N);
    std::normal_distribution<double> nx(0.0, 1.0);
    for (int i = 0; i < xVec.size(); ++i) { xVec(i) = nx(engine); }
    auto idxVec = samplingWoutReplace(
            engine, std::vector<bool>(ns_LASSO::N), ns_LASSO::N - ns_LASSO::NON_ZERO
    );
    for (const auto &idx: idxVec) { xVec(static_cast<int>(idx)) = 0.0; }
    LOG_VAR(xVec.transpose())

    // generate vector b
    Eigen::VectorXd bVec = AMat * xVec;
    // std::normal_distribution<double> n(0.0, ns_LASSO::SIGMA);
    // for (int i = 0; i < ns_LASSO::M; ++i) { bVec(i) += n(engine); }
    LOG_VAR(bVec.transpose())

    // Eigen::JacobiSVD<Eigen::MatrixXd> svd(AMat.transpose() * AMat, Eigen::ComputeEigenvectors);
    // double alpha = 1.0 / svd.singularValues()(0);
    // LOG_VAR(alpha)

    LOG_VAR(ns_na::LASSO(AMat, xVec, bVec, ns_LASSO::MU))
    LOG_VAR(ns_na::LASSO_HUBER_SMOOTH(AMat, xVec, bVec, ns_LASSO::MU, ns_LASSO::HUBER_DELTA))

    // solve
    Eigen::VectorXd xVecSolve = xVec;
    ns_na::LASSO_SOLVER(
            AMat, xVecSolve, bVec, ns_LASSO::MU, ns_LASSO::ALPHA,
            ns_LASSO::HUBER_DELTA, ns_LASSO::FUNC_THD, ns_LASSO::GRAD_THD
    );
    LOG_VAR(xVec.transpose())
    LOG_VAR(xVecSolve.transpose())
    ns_na::PrintVec(xVec);
    ns_na::PrintVec(xVecSolve);
}

int main() {
    ns_log::ns_priv::stdLogger.setPrecision(10);
    LASSOSolver();
    return 0;
}