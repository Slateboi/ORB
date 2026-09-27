#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <algorithm>

struct Corner{
    int x;
    int y;
    int score;
};  

const cv::Point FAST_CIRCLE[16] =
{
    { 0, -3},
    { 1, -3},
    { 2, -2},
    { 3, -1},

    { 3,  0},
    { 3,  1},
    { 2,  2},
    { 1,  3},

    { 0,  3},
    {-1,  3},
    {-2,  2},
    {-3,  1},

    {-3,  0},
    {-3, -1},
    {-2, -2},
    {-1, -3}
};

const std::vector dx = {-1, 0, 1, -1, 1, -1, 0, 1};
const std::vector dy = {-1, -1, -1, 0, 0, 1, 1, 1};

int classifyPixel(int centerIntensity, int neighbourIntensity, int threshold){

    if(neighbourIntensity > centerIntensity + threshold){
        return 1;
    }

    if(neighbourIntensity < centerIntensity - threshold){
        return -1;
    }

    return 0;
}

int isFastCorner(const cv::Mat& image, int x, int y, int threshold){

    const int center = static_cast<int>(image.at<uchar>(cv::Point(x, y)));

    constexpr int REQUIRED = 9;

    int states[16];
    int score = 0;

    for(int i = 0; i < 16; i++){
        int nx = x + FAST_CIRCLE[i].x;
        int ny = y + FAST_CIRCLE[i].y;

        int neighbour = static_cast<int>(image.at<uchar>(cv::Point(nx, ny)));

        states[i] = classifyPixel(center, neighbour, threshold);
        score += std::abs(neighbour - center);

        //std::cout << neighbour << " " << center << " ";
        //std::cout << states[i] << std::endl;

    }

    for(int i = 0; i < 16; i++){

        bool allBright = true;
        bool allDark = true;

        for(int k = 0; k < REQUIRED; k++){
            int index = (i + k) % 16;

            if(states[index] != 1){
                allBright = false;
            }
            if(states[index] != -1){
                allDark = false;
            }

        }

        if(allBright || allDark){
            return score;
        }
    }

    return 0;
}


std::vector<Corner> detectFast(const cv::Mat& image, int threshold){

    std::vector<Corner> corners;
    
    constexpr int BORDER = 3;

    for(int y = BORDER; y < image.rows - BORDER; y++){
        for(int x = BORDER; x < image.cols - BORDER; x++){
            int score = isFastCorner(image, x, y, threshold);
            if(score > 0){
                corners.push_back({x, y, score});
            }
        }
    }

    return corners;
}


std::vector<Corner> nonMaximumSuppression(const std::vector<Corner>& corners, int width, int height){
    std::vector<Corner> result;
    std::vector<std::vector<int>> scoreMap(height, std::vector<int>(width, 0));
    constexpr int NMS_POINTS = 8;
    //std::cout << corners.size() << std::endl;

    for(const Corner& corner: corners){
        scoreMap[corner.y][corner.x] = corner.score;
    }

    for(const Corner& corner : corners){
        bool isMax = true;

        for(int i = 0; i < 8; i++){
            int nx = corner.x + dx[i];
            int ny = corner.y + dy[i];

            if(nx < 0 || nx >= width || ny < 0 || ny >= height){
                continue;
            }

            if(scoreMap[ny][nx] > corner.score){
                isMax = false;
                break;
            }
        }

        if(isMax){
            result.push_back(corner);
        }

    }
   
    return result;
    
}


std::vector<cv::Mat> buildImagePyramid(cv::Mat& image, int levels){
    constexpr int scaleFactor = 2;
    std::vector<cv::Mat> imagePyramid
    for(int i = 0; i < levels, i++){
        int scale 
    }
}



int main(int argc, char** argv){
    
    if(argc < 3){
        std::cerr << "Usage: ./orb image.jpg threshold\n";
        return 1;
    }

    cv::Mat gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    if(gray.empty()){
        std::cerr << "Could not load image.\n";
        return 1;
    }

    std::cout << "Image width: " << gray.cols << "\n";
    std::cout << "Image height: " << gray.rows << "\n";

    std::vector<Corner> corners = detectFast(gray, std::stoi(argv[2]));

    cv::imshow("", gray);
    cv::waitKey(0);

    std::cout << corners.size() << std::endl;

    corners = nonMaximumSuppression(corners, gray.rows, gray.cols);

    std::cout << corners.size() << std::endl;

    for (const Corner& corner : corners)
    {
        cv::circle(
            gray,
            cv::Point(corner.x, corner.y),
            10,
            cv::Scalar(0, 0, 255),
            1
        );
    }

    cv::imshow(
        "FAST from scratch",
        gray
    );

    cv::waitKey(0);

    return 0;
}
