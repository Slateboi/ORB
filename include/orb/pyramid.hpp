#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "orb/types.hpp"


namespace orb{
    std::vector<cv::Mat> buildImagePyramid(cv::Mat& image, int levels);
    void coordinateScaling(std::vector<Corner>& corners, int level);
}