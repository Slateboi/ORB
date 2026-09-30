#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "orb/types.hpp"

namespace orb{

    std::vector<Corner> detectFast(const cv::Mat& image, int threshold);
    std::vector<Corner> nonMaximumSuppression(const std::vector<Corner>& corners, int width, int height);
}


