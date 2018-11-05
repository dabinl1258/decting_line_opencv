cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
project(hough_line)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(hough_line main.cpp)
target_link_libraries(hough_line ${OpenCV_LIBS})
