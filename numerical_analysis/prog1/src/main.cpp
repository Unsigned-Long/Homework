#include "lu_factorization.h"
#include "steep_desc.h"
#include "artwork/logger/logger.h"

constexpr int MAT_SIZE = 10;

void TestEquSolvingByLU() {
    Eigen::MatrixXd AMat = Eigen::MatrixXd::Random(MAT_SIZE, MAT_SIZE);
    Eigen::VectorXd xVec = Eigen::VectorXd::Random(MAT_SIZE);
    Eigen::VectorXd bVec = AMat * xVec;
    Eigen::VectorXd xVecRes;
    spdlog::stopwatch sw;
    ns_na::EquSolvingByLU(AMat, bVec, xVecRes);
    ns_log::ns_priv::stdLogger._precision = 20;
    LOG_VAR((xVec - xVecRes).norm())
    spdlog::info("total runtime: {} (s)", sw);
}

void TestSteepestDescent1() {
    Eigen::MatrixXd AMat(2, 2);
    AMat << 3, 2, 2, 6;
    Eigen::VectorXd bVec(2);
    bVec << 2, -8;
    Eigen::VectorXd xVec0(2);
    xVec0 << -2, -2;
    // xVec0 << 5, 2;
    Eigen::VectorXd xVec;
    LOG_VAR(AMat)
    LOG_VAR(bVec.transpose())
    ns_na::steepest_descent(AMat, bVec, xVec0, xVec);
    LOG_VAR((AMat * xVec).transpose())
}

void TestSteepestDescent2() {
    Eigen::MatrixXd AMat = Eigen::MatrixXd::Zero(MAT_SIZE, MAT_SIZE);
    for (int i = 1; i < MAT_SIZE; ++i) {
        AMat(i, i) = 2.0;
        AMat(i, i - 1) = AMat(i - 1, i) = -1.0;
    }
    AMat(0, 0) = 2.0;

    Eigen::VectorXd xVec = Eigen::VectorXd::Random(MAT_SIZE);
    Eigen::VectorXd bVec = AMat * xVec;

    Eigen::VectorXd xVec0 = Eigen::VectorXd::Zero(MAT_SIZE);
    Eigen::VectorXd xVecRes;
    spdlog::stopwatch sw;
    ns_na::steepest_descent(AMat, bVec, xVec0, xVecRes);
    spdlog::info("total runtime: {} (s)", sw);

    ns_log::ns_priv::stdLogger._precision = 20;
    LOG_VAR((xVec - xVecRes).squaredNorm())
}

int main() {
    // for (int i = 0; i < 5; ++i) {
    //     TestEquSolvingByLU();
    // }
    // TestSteepestDescent1();
    TestSteepestDescent2();
    return 0;
}