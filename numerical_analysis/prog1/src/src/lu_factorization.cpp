#include "../include/lu_factorization.h"

namespace ns_na {

    void LUFactorization(const Eigen::MatrixXd &AMat, Eigen::MatrixXd &LMat, Eigen::MatrixXd &UMat) {
        assert(AMat.rows() == AMat.cols());
        auto n = AMat.rows();

        LMat = Eigen::MatrixXd::Identity(n, n);
        UMat = AMat;
        for (int c = 0; c < n - 1; ++c) {
            Eigen::MatrixXd curLMatInv = Eigen::MatrixXd::Identity(n, n);
            for (int r = c + 1; r < n; ++r) {
                double l = UMat(r, c) / UMat(c, c);
                curLMatInv(r, c) = l;
                UMat.row(r) = UMat.row(r) - l * UMat.row(c);
            }
            LMat = LMat * curLMatInv;
        }
    }

    void EquSolvingByLU(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &bVec, Eigen::VectorXd &xVec) {
        assert(AMat.rows() == AMat.cols());
        assert(AMat.rows() == bVec.rows());
        auto n = AMat.rows();

        Eigen::MatrixXd LMat, UMat;
        spdlog::stopwatch sw;
        ns_na::LUFactorization(AMat, LMat, UMat);
        spdlog::info("lu factorization runtime: {} (s)", sw);
        // A = LU, LUx = b, Ly = b, Ux = y
        // ------
        // Ly = b
        // ------
        Eigen::VectorXd yVec(n);
        yVec(0) = bVec(0) / LMat(0, 0);
        for (int r = 1; r < n; ++r) {
            yVec(r) = bVec(r) - (LMat.block(r, 0, 1, r) * yVec.block(0, 0, r, 1))(0, 0);
        }
        // ------
        // Ux = y
        // ------
        xVec = Eigen::VectorXd(n);
        xVec(n - 1) = yVec(n - 1) / UMat(n - 1, n - 1);
        for (int r = static_cast<int>(n) - 2; r >= 0; --r) {
            xVec(r) = (yVec(r) - (UMat.block(r, r + 1, 1, n - r - 1)
                                  * xVec.block(r + 1, 0, n - r - 1, 1))(0, 0)) / UMat(r, r);
        }
    }
}