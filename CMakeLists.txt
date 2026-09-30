cmake_minimum_required(VERSION 3.10)

project(ORBMonocular)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(
    orb
    src/main.cpp
    src/fast.cpp
    src/pyramid.cpp
)

target_include_directories(
    orb
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    orb
    ${OpenCV_LIBS}
)