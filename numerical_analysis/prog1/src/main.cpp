#include "lu_factorization.h"

constexpr int MAT_SIZE = 10;

int main() {
    Eigen::MatrixXd AMat = Eigen::MatrixXd::Random(MAT_SIZE, MAT_SIZE);
    Eigen::VectorXd xVec = Eigen::VectorXd::Random(MAT_SIZE);
    Eigen::VectorXd bVec = AMat * xVec;
    Eigen::VectorXd xVecRes;
    ns_na::EquSolvingByLU(AMat, bVec, xVecRes);
    LOG_VAR(AMat)
    LOG_VAR(xVec.transpose())
    LOG_VAR(xVecRes.transpose())
    return 0;
}