#ifndef OPT_SOLVER_LASSO_H
#define OPT_SOLVER_LASSO_H

#include "Eigen/Dense"
#include "random"
#include "artwork/logger/logger.h"

namespace ns_na {

    double LASSO(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &xVec,
                 const Eigen::VectorXd &bVec, double mu) {
        return 0.5 * (AMat * xVec - bVec).squaredNorm() + mu * xVec.cwiseAbs().sum();
    }

    double LASSO_HUBER_SMOOTH(const Eigen::MatrixXd &AMat, const Eigen::VectorXd &xVec,
                              const Eigen::VectorXd &bVec, double mu, double delta) {
        double v1 = 0.5 * (AMat * xVec - bVec).squaredNorm();
        double v2 = 0.0;
        for (int i = 0; i < xVec.size(); ++i) {
            const double &val = xVec(i);
            if (std::abs(val) < delta) {
                v2 += 0.5 * val * val / delta;
            } else {
                v2 += std::abs(val) - delta * 0.5;
            }
        }
        return v1 + mu * v2;
    }

    void LASSO_SOLVER(const Eigen::MatrixXd &AMat, Eigen::VectorXd &x, const Eigen::VectorXd &bVec, double mu,
                      double alpha0, double huberDelta, double funcThd, double gradThd) {
        auto n = AMat.cols();
        x = Eigen::VectorXd::Zero(n);
        while (true) {
            // compute grad
            Eigen::VectorXd J = AMat.transpose() * (AMat * x - bVec);
            for (int j = 0; j < n; ++j) {
                double h;
                if (std::abs(x(j)) > huberDelta) {
                    if (x(j) > 0.0) { h = 1.0; } else { h = -1.0; }
                } else { h = x(j) / huberDelta; }
                J(j) += mu * h;
            }
            double e = LASSO_HUBER_SMOOTH(AMat, x, bVec, mu, huberDelta);


            Eigen::MatrixXd H = J * J.transpose();
            Eigen::VectorXd b = -J * e;
            LOG_VAR(J.transpose())
            LOG_VAR(b.transpose())
            LOG_VAR(e)
            Eigen::VectorXd deltaX = (H.transpose() * H).inverse() * (H.transpose() * b);
            LOG_VAR(deltaX.transpose())
            LOG_VAR(deltaX.norm())
            std::cin.get();
            if (deltaX.norm() < funcThd) {
                break;
            } else {
                x += deltaX;
            }
        }
    }

    void LASSO_TEMP(const Eigen::MatrixXd &AMat, Eigen::VectorXd &x, const Eigen::VectorXd &bVec, double mu,
                    double alpha0, double huberDelta, double funcThd, double gradThd) {
        auto n = AMat.cols();

        // compute grad
        Eigen::VectorXd g = AMat.transpose() * (AMat * x - bVec);
        for (int j = 0; j < n; ++j) {
            double h;
            if (std::abs(x(j)) > huberDelta) {
                if (x(j) > 0.0) { h = 1.0; } else { h = -1.0; }
            } else { h = x(j) / huberDelta; }
            g(j) += mu * h;
        }
        LOG_VAR(g.transpose())

        double nrmG = g.norm();

        double f = LASSO_HUBER_SMOOTH(AMat, x, bVec, mu, huberDelta);

        double alpha = alpha0;

        constexpr static double eta = 0.2;
        constexpr static double rho = 1E-6;
        constexpr static double gamma = 0.85;

        double Q = 1.0;
        double Cval = f;

        int iter = 0;

        while (true) {
            Eigen::VectorXd xp = x;
            Eigen::VectorXd gp = g;
            double fp = f;

            for (int i = 0; i < 10; ++i) {
                x = xp - alpha * gp;

                g = AMat.transpose() * (AMat * x - bVec);
                for (int j = 0; j < n; ++j) {
                    double h;
                    if (std::abs(x(j)) > huberDelta) {
                        if (x(j) > 0.0) { h = 1.0; } else { h = -1.0; }
                    } else { h = x(j) / huberDelta; }
                    g(j) += mu * h;
                }

                f = LASSO_HUBER_SMOOTH(AMat, x, bVec, mu, huberDelta);

                if (f <= Cval - alpha * rho * nrmG * nrmG) {
                    break;
                } else {
                    alpha *= eta;
                }
            }

            nrmG = g.norm();

            LOG_VAR(std::abs(fp - f))

            if (nrmG < gradThd || std::abs(fp - f) < funcThd) { break; }

            Eigen::VectorXd dx = x - xp;
            Eigen::VectorXd dg = g - gp;
            double dxg = std::abs(dx.dot(dg));
            if (dxg > 0) {
                if (iter % 2 == 0) {
                    alpha = dx.squaredNorm() / dxg;
                } else {
                    alpha = dxg / dg.squaredNorm();
                }
                alpha = std::max(std::min(alpha, 1e12), 1e-12);
            }
            double Qp = Q;
            Q = gamma * Qp + 1;
            Cval = (gamma * Qp * Cval + f) / Q;

            ++iter;
        }
    }

    void PrintVec(const Eigen::VectorXd &vec) {
        for (int i = 0; i < vec.size(); ++i) {
            std::cout << vec(i) << ',';
        }
        std::cout << std::endl << std::endl;
    }
}

#endif //OPT_SOLVER_LASSO_H
