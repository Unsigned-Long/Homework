// Copyright (c) 2023. Created on 9/29/23 10:16 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "extractor.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "filesystem"
#include "fstream"
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

void DetectCorners(const std::string &imgPath, std::string outputFolder) {
    auto img = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
    // convert to gray image
    cv::Mat gImg;
    cv::cvtColor(img, gImg, cv::COLOR_BGR2GRAY);

    auto res = ns_mv::CornerExtractor::Create(ns_mv::CornerExtractor::ExtractorType::FAST)->Process(gImg);

    // output
    if (!std::filesystem::exists(outputFolder)) {
        std::filesystem::create_directories(outputFolder);
    }
    // corners
    std::vector<ns_mv::Corner> corners;
    std::transform(res.first.begin(), res.first.end(), std::back_inserter(corners),
                   [](const ns_mv::Entity::Ptr &cor) {
                       return *dynamic_cast<ns_mv::Corner *>(cor.get());
                   });
    {
        std::cout << "save corners: " << corners.size() << std::endl;
        std::ofstream file(outputFolder + "/corner.json");
        cereal::JSONOutputArchive ar(file);
        ar(cereal::make_nvp("corners", corners));
    }
    {
        for (const auto &[name, mat]: res.second) {
            std::cout << "save image named '" << name << "'" << std::endl;
            cv::imwrite(outputFolder.append("/" + name + ".jpg"), mat);
        }
    }
}

void DetectLines(const std::string &imgPath, std::string outputFolder) {
    auto img = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
    // convert to gray image
    cv::Mat gImg;
    cv::cvtColor(img, gImg, cv::COLOR_BGR2GRAY);

    auto res = ns_mv::LineExtractor::Create(ns_mv::LineExtractor::ExtractorType::LSD_COMPLEX)->Process(gImg);

    // output
    if (!std::filesystem::exists(outputFolder)) {
        std::filesystem::create_directories(outputFolder);
    }
    // lines
    std::vector<ns_mv::Line> lines;
    std::transform(res.first.begin(), res.first.end(), std::back_inserter(lines),
                   [](const ns_mv::Entity::Ptr &l) {
                       return *dynamic_cast<ns_mv::Line *>(l.get());
                   });
    {
        std::cout << "save lines: " << lines.size() << std::endl;
        std::ofstream file(outputFolder + "/line.json");
        cereal::JSONOutputArchive ar(file);
        ar(cereal::make_nvp("lines", lines));
    }
    {
        for (const auto &[name, mat]: res.second) {
            std::cout << "save image named '" << name << "'" << std::endl;
            cv::imwrite(outputFolder.append("/" + name + ".jpg"), mat);
        }
    }
}

int main(int argc, char **argv) {
    try {
        std::string imgPath = "/home/csl/Homework/machine_vision/prog1/data/img2.jpg";
        std::string outputFolder = "/home/csl/Homework/machine_vision/prog1/data/lsd_complex/img2";

        // DetectCorners(imgPath, outputFolder);
        DetectLines(imgPath, outputFolder);
    } catch (const std::exception &e) {
        std::cout << "error happens: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}