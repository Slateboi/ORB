cmake_minimum_required(VERSION 3.10)

project(ORBFromScratch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer Ubuntu's packaged, CPU-only OpenCV.  A separate OpenCV installation
# under /usr/local was built with CUDA 12.9 and cannot be loaded with the
# system's CUDA 11.5 toolkit.  Override ORB_OPENCV_DIR if a different CPU-only
# OpenCV package should be used.
set(
    ORB_OPENCV_DIR
    "/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/opencv4"
    CACHE PATH
    "Directory containing the CPU-only OpenCVConfig.cmake"
)

if(NOT EXISTS "${ORB_OPENCV_DIR}/OpenCVConfig.cmake")
    message(FATAL_ERROR
        "CPU-only OpenCV was not found at ${ORB_OPENCV_DIR}. "
        "Install libopencv-dev or set ORB_OPENCV_DIR to another CPU-only OpenCV package."
    )
endif()

# Force this project's OpenCV selection even if an older configure cached the
# incompatible /usr/local package in OpenCV_DIR.
set(OpenCV_DIR "${ORB_OPENCV_DIR}" CACHE PATH "OpenCV package directory" FORCE)
find_package(OpenCV 4 REQUIRED COMPONENTS core imgcodecs highgui)
message(STATUS "Using OpenCV ${OpenCV_VERSION} from ${OpenCV_DIR}")

add_executable(orb
    src/main.cpp
)

target_link_libraries(orb
    ${OpenCV_LIBS}
)
