// Copyright (c) 2023. Created on 9/29/23 10:16 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "filesystem"
#include "fstream"
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

int main(int argc, char **argv) {
    try {
        std::string imgPath = "/home/csl/Homework/machine_vision/prog1/data/img2.jpg";
        std::string outputFolder = "/home/csl/Homework/machine_vision/prog1/data/harris/img2";

    } catch (const std::exception &e) {
        std::cout << "error happens: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}