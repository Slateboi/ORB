#include <opencv2/opencv.hpp>

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>


#include "orb/types.hpp"
#include "orb/pyramid.hpp"
#include "orb/fast.hpp"


int main(int argc, char** argv){

    constexpr int LEVELS = 4;
    
    if(argc < 3){
        std::cerr << "Usage: ./orb image.jpg threshold\n";
        return 1;
    }

    cv::Mat gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    if(gray.empty()){
        std::cerr << "Could not load image.\n";
        return 1;
    }

    std::vector<cv::Mat> imagePyramid = orb::buildImagePyramid(gray, LEVELS);

    std::cout << "Image width: " << gray.cols << "\n";
    std::cout << "Image height: " << gray.rows << "\n";

    std::vector<std::vector<orb::Corner>> imagePyramidCorners;

    for(int level = 0; level < LEVELS; level++){
        std::vector<orb::Corner> corners = orb::detectFast(imagePyramid[level], std::stoi(argv[2]));
        corners = orb::nonMaximumSuppression(corners, imagePyramid[level].rows, imagePyramid[level].cols);

        for(orb::Corner& corner : corners){
            corner.level = level;
        }

        imagePyramidCorners.push_back(corners);

        std::cout << imagePyramid[level].rows << " " << imagePyramid[level].cols << std::endl;
    }

    //std::vector<Corner> corners = detectFast(gray, std::stoi(argv[2]));

    for(const std::vector<orb::Corner>& corners : imagePyramidCorners){
        std::cout << corners.size() << std::endl;
    }
    return 0;
}
