#include "lu_factorization.h"
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

int main() {
    for (int i = 0; i < 5; ++i) {
        TestEquSolvingByLU();
    }
    return 0;
}