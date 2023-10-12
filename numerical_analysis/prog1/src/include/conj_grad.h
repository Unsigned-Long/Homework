#ifndef EQU_SOLVER_CONJ_GRAD_H
#define EQU_SOLVER_CONJ_GRAD_H

#include "Eigen/Dense"
#include "artwork/logger/logger.h"

namespace ns_na {
    void conjugate_gradient(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec,
                            const Eigen::VectorXd &xVec0, Eigen::VectorXd &xVec, double thresh = 1E-10);
}


#endif //EQU_SOLVER_CONJ_GRAD_H
