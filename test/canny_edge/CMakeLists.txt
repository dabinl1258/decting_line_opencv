cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
project(canny_edge)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(canny_edge main.cpp)
target_link_libraries(canny_edge ${OpenCV_LIBS})
