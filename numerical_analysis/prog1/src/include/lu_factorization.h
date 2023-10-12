#ifndef PROG1_LU_FACTORIZATION_H
#define PROG1_LU_FACTORIZATION_H

#include "Eigen/Dense"
#include "spdlog/stopwatch.h"
#include "spdlog/spdlog.h"

namespace ns_na {
    void LUFactorization(const Eigen::MatrixXd &AMat, Eigen::MatrixXd &LMat, Eigen::MatrixXd &UMat);

    void EquSolvingByLU(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec, Eigen::VectorXd &xVec);
}
#endif //PROG1_LU_FACTORIZATION_H
