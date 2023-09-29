// Copyright (c) 2023. Created on 9/29/23 10:16 AM by shlchen@whu.edu.cn (Shuolong Chen), who received the B.S. degree in
// geodesy and geomatics engineering from Wuhan University, Wuhan China, in 2023. He is currently a master candidate at
// the school of Geodesy and Geomatics, Wuhan University. His area of research currently focuses on integrated navigation
// systems and multi-sensor fusion.

#include "extractor.h"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/line_descriptor.hpp"

namespace ns_mv {

    Extractor::Extractor() = default;

    std::pair<std::vector<Entity::Ptr>, std::map<std::string, cv::Mat>> CornerExtractor::Process(cv::Mat img) {
        std::vector<Entity::Ptr> corners;
        std::map<std::string, cv::Mat> mats;
        switch (type) {
            case ExtractorType::HARRIS: {
                std::cout << "HARRIS" << std::endl;
                // perform harris corner detect
                cv::Mat dstImg;
                cv::cornerHarris(img, dstImg, 2, 3, 0.04);
                mats.insert({"response", ns_mv::ConvertToVisibleMat(dstImg, 0.01, 0.01)});

                // find the min and max value
                double min, max;
                cv::minMaxIdx(dstImg, &min, &max);
                // convert the dstImg to binary image based on the threshold
                cv::Mat filteredImg;
                cv::threshold(dstImg, filteredImg, (max + min) * 0.2, 255, cv::ThresholdTypes::THRESH_BINARY);
                mats.insert({"binary_corner", filteredImg});

                // mark corners to source image
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                int rows = img.rows, cols = img.cols;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        float val = filteredImg.at<float>(i, j);
                        if (val == 255.0) {
                            corners.push_back(Corner::Create(cv::Point2f((float) j, (float) i)));
                        }
                    }
                }

                for (const auto &elem: corners) {
                    elem->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
            case ExtractorType::SIFT: {
                std::cout << "SIFT" << std::endl;
                auto detector = cv::SIFT::create(1000);
                std::vector<cv::KeyPoint> keyPoints;
                detector->detect(img, keyPoints);
                for (const auto &point: keyPoints) {
                    corners.push_back(Corner::Create(point.pt));
                }

                // mark corners to source image
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &cor: corners) {
                    cor->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
            case ExtractorType::SURF: {
                std::cout << "SURF" << std::endl;
                auto detector = cv::xfeatures2d::SURF::create(1000);
                std::vector<cv::KeyPoint> keyPoints;
                detector->detect(img, keyPoints);

                for (const auto &point: keyPoints) {
                    corners.push_back(Corner::Create(point.pt));
                }

                // mark corners to source image
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &cor: corners) {
                    cor->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
            case ExtractorType::ORB: {
                std::cout << "ORB" << std::endl;
                auto detector = cv::ORB::create(1000);
                std::vector<cv::KeyPoint> keyPoints;
                detector->detect(img, keyPoints);

                for (const auto &point: keyPoints) {
                    corners.push_back(Corner::Create(point.pt));
                }

                // mark corners to source image
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &cor: corners) {
                    cor->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
            case ExtractorType::FAST: {
                std::cout << "FAST" << std::endl;
                auto detector = cv::FastFeatureDetector::create(60);
                std::vector<cv::KeyPoint> keyPoints;
                detector->detect(img, keyPoints);

                for (const auto &point: keyPoints) {
                    corners.push_back(Corner::Create(point.pt));
                }

                // mark corners to source image
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &cor: corners) {
                    cor->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
        }
        // for (const auto &[name, mat]: mats) {
        //     ShowImg(mat, name);
        // }
        return {corners, mats};
    }

    CornerExtractor::Ptr CornerExtractor::Create(CornerExtractor::ExtractorType type) {
        return std::make_shared<CornerExtractor>(type);
    }

    CornerExtractor::CornerExtractor(CornerExtractor::ExtractorType type) : type(type) {}


    std::pair<std::vector<Entity::Ptr>, std::map<std::string, cv::Mat>> LineExtractor::Process(cv::Mat img) {
        std::vector<Entity::Ptr> lines;
        std::map<std::string, cv::Mat> mats;
        switch (type) {

            case ExtractorType::LSD_SAMPLE: {
                std::cout << "LSD_SAMPLE" << std::endl;
                auto lsd = cv::createLineSegmentDetector();
                std::vector<cv::Vec4f> cvLines;
                lsd->detect(img, cvLines);

                // mark corners to source image
                for (const auto &elem: cvLines) {
                    lines.push_back(Line::Create({elem[0], elem[1]}, {elem[2], elem[3]}));
                }
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &elem: lines) {
                    elem->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
            case ExtractorType::LSD_COMPLEX: {
                std::cout << "LSD_COMPLEX" << std::endl;
                auto lsd = cv::line_descriptor::LSDDetector::createLSDDetector();
                std::vector<cv::line_descriptor::KeyLine> cvLines;
                lsd->detect(img, cvLines, 2, 1);

                // mark corners to source image
                for (const auto &elem: cvLines) {
                    lines.push_back(Line::Create({elem.startPointX, elem.startPointY},
                                                 {elem.endPointX, elem.ePointInOctaveY}));
                }
                cv::Mat markedImg;
                cv::cvtColor(img, markedImg, cv::COLOR_GRAY2BGR);
                for (const auto &elem: lines) {
                    elem->Draw(markedImg);
                }
                mats.insert({"marked_image", markedImg});
            }
                break;
        }
        return {lines, mats};
    }

    LineExtractor::Ptr LineExtractor::Create(LineExtractor::ExtractorType type) {
        return std::make_shared<LineExtractor>(type);
    }

    LineExtractor::LineExtractor(LineExtractor::ExtractorType type) : type(type) {}
}