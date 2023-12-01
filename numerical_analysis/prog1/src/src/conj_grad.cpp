#include "conj_grad.h"

namespace ns_na {

    void conjugate_gradient(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec, const Eigen::VectorXd &xVec0,
                            Eigen::VectorXd &xVec, double thresh) {
        xVec = xVec0;
        Eigen::VectorXd rVec = bVec - AMat * xVec;
        Eigen::VectorXd pVec = rVec;
        int count = 0;
        while (true) {
            LOG_VAR(count)
            ++count;
            // LOG_VAR(xVec.transpose())
            Eigen::VectorXd ap = AMat * pVec;
            double alpha = rVec.dot(pVec) / ap.dot(pVec);
            LOG_VAR(alpha)
            xVec = xVec + alpha * pVec;
            LOG_VAR(xVec.transpose())
            if (alpha * pVec.squaredNorm() < thresh) {
                break;
            }
            double beta1 = rVec.dot(rVec);
            rVec = rVec - alpha * ap;
            double beta2 = rVec.dot(rVec) / beta1;
            pVec = rVec + beta2 * pVec;
            LOG_VAR(pVec.transpose())
        }
        LOG_VAR(count)
    }
}