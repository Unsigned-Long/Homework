// Copyright (c) 2023. Created on 9/30/23 2:44 PM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "kalman_filter.h"
#include "argparse.hpp"
#include "config.h"
#include "filesystem"
#include "cereal/types/vector.hpp"

std::vector<ns_kf::Measure> LoadMeasurements(const std::string &filename) {
    return {};
}

int main(int argc, char **argv) {
    argparse::ArgumentParser prog("kalman_filter");
    prog.add_argument("config").help("the path of the configure file");

    try {
        // load the config file
        prog.parse_args(argc, argv);
        auto c = ns_kf::Config::Load(prog.get<std::string>("config"));
        std::cout << c << std::endl;
        std::cin.get();

        // perform filter
        std::vector<ns_kf::State> estStates, preStates;
        auto filter = ns_kf::KalmanFilter::Create(c.init_state, c.kx, c.ky, c.gravity, c.sigma_ex, c.sigma_ey);

        for (const auto &mes: LoadMeasurements(c.data_path)) {

            filter->StatePredict(mes.timestamp);
            preStates.push_back(filter->GetPreState());

            switch (c.mode) {

                case ns_kf::SolveMode::GLOBAL_EKF: {
                    filter->MesUpdateGlobal(mes);
                }
                    break;
                case ns_kf::SolveMode::LOCAL_EKF_1: {
                    filter->MesUpdateSequentially1(mes);
                }
                    break;
                case ns_kf::SolveMode::LOCAL_EKF_2: {
                    filter->MesUpdateSequentially2(mes);
                }
                    break;
            }
            estStates.push_back(filter->GetEstState());
        }

        // output results
        if (!std::filesystem::exists(c.output_path)) {
            std::filesystem::create_directories(c.output_path);
        }
        {
            std::ofstream file(c.output_path + "/results.xml");
            auto ar = cereal::XMLOutputArchive(file);
            ar(
                    cereal::make_nvp("est_states", estStates),
                    cereal::make_nvp("pre_states", preStates)
            );
        }

    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << prog;
    }

    return 0;
}