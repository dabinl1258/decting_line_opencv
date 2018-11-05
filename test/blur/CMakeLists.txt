cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
project(blur)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(blur main.cpp)
target_link_libraries(blur ${OpenCV_LIBS})
