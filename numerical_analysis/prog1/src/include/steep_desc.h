#ifndef EQU_SOLVER_STEEP_DESC_H
#define EQU_SOLVER_STEEP_DESC_H

#include "Eigen/Dense"
#include "artwork/logger/logger.h"

namespace ns_na {
    void steepest_descent(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec,
                          const Eigen::VectorXd &xVec0, Eigen::VectorXd &xVec, double thresh = 1E-10);
}

#endif //EQU_SOLVER_STEEP_DESC_H
