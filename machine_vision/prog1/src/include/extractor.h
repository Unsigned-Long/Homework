// Copyright (c) 2023. Created on 9/29/23 10:16 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef PROG1_EXTRACTOR_H
#define PROG1_EXTRACTOR_H

#include "memory"
#include "entity.h"
#include "opencv4/opencv2/core.hpp"
#include "map"

namespace ns_mv {
    class Extractor {
    public:
        using Ptr = std::shared_ptr<Extractor>;

    public:
        Extractor();

        virtual std::pair<std::vector<Entity::Ptr>, std::map<std::string, cv::Mat>> Process(cv::Mat img) = 0;
    };

    class CornerExtractor : public Extractor {
    public:
        using Ptr = std::shared_ptr<CornerExtractor>;

        enum class ExtractorType {
            HARRIS, SIFT, SURF, ORB, FAST
        };

        ExtractorType type;
    public:
        explicit CornerExtractor(ExtractorType type);

        static Ptr Create(ExtractorType type);

        std::pair<std::vector<Entity::Ptr>, std::map<std::string, cv::Mat>> Process(cv::Mat img) override;
    };

    class LineExtractor : public Extractor {
    public:
        using Ptr = std::shared_ptr<LineExtractor>;

        enum class ExtractorType {
            LSD_SAMPLE, LSD_COMPLEX
        };

        ExtractorType type;

    public:
        explicit LineExtractor(ExtractorType type);

        static Ptr Create(ExtractorType type);

        std::pair<std::vector<Entity::Ptr>, std::map<std::string, cv::Mat>> Process(cv::Mat img) override;
    };
}

#endif //PROG1_EXTRACTOR_H
