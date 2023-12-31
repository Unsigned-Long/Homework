// Copyright (c) 2023. Created on 9/29/23 10:17 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#ifndef EXTRACTOR_ENTITY_H
#define EXTRACTOR_ENTITY_H

#include <ostream>
#include "memory"
#include "colour.h"
#include "utils.hpp"

namespace ns_mv {
    struct Entity {
    public:
        static pangolin::ColourWheel WHEEL;

        using Ptr = std::shared_ptr<Entity>;

        virtual std::string Type() { return "Entity"; }

        virtual void Draw(const cv::Mat &img) = 0;
    };

    struct Corner : public Entity {
    public:
        using Ptr = std::shared_ptr<Corner>;

    public:
        cv::Point2f p;

    public:
        explicit Corner(cv::Point2f pos);

        static Ptr Create(const cv::Point2f &pos);

        std::string Type() override;

        void Draw(const cv::Mat &img) override;

        friend std::ostream &operator<<(std::ostream &os, const Corner &corner);

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(p));
        }

    };

    struct Line : public Entity {
    public:
        using Ptr = std::shared_ptr<Line>;

    public:
        cv::Point2f p1, p2;

        Line(cv::Point2f p1, cv::Point2f p2);

        static Ptr Create(const cv::Point2f &p1, const cv::Point2f &p2);

        std::string Type() override;

        void Draw(const cv::Mat &img) override;

        friend std::ostream &operator<<(std::ostream &os, const Line &line);

    public:
        // Serialization
        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(p1), CEREAL_NVP(p2));
        }

    };

}


#endif //EXTRACTOR_ENTITY_H
