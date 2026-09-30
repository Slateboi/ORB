#include "orb/pyramid.hpp"

#include <cmath>

namespace orb{

    static const float scaleFactor = 1.2f;
}

namespace orb{
        std::vector<cv::Mat> buildImagePyramid(cv::Mat& image, int levels){
        std::vector<cv::Mat> imagePyramid;
        imagePyramid.push_back(image.clone());
        for(int level = 1; level < levels; level++){

            float scale = 1.0f / std::pow(scaleFactor, level);

            cv::Mat scaledImage;

            cv::resize(image, scaledImage, cv::Size(), scale, scale, cv::INTER_LINEAR);

            imagePyramid.push_back(scaledImage);
        }

        return imagePyramid;
    }

    void coordinateScaling(std::vector<Corner>& corners, int level){

        float scale = std::pow(scaleFactor, level);

        for(Corner& corner : corners){
            corner.level = level;

            corner.originalx = scale * corner.x;
            corner.originaly = scale * corner.y;
        }

    }
}
