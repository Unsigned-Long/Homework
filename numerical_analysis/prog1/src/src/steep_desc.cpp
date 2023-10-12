#include "steep_desc.h"

namespace ns_na {

    void steepest_descent(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec, const Eigen::VectorXd &xVec0,
                          Eigen::VectorXd &xVec, double thresh) {
        xVec = xVec0;
        Eigen::VectorXd rVec = bVec - AMat * xVec;
        int count = 0;
        while (true) {
            ++count;
            // LOG_VAR(xVec.transpose())
            Eigen::VectorXd ar = AMat * rVec;
            double alpha = rVec.dot(rVec) / rVec.dot(ar);
            xVec = xVec + alpha * rVec;
            if (alpha * rVec.squaredNorm() < thresh) {
                break;
            }
            rVec = rVec - alpha * ar;
        }
        LOG_VAR(count)
    }
}
