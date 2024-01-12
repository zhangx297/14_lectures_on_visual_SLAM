cmake_minimum_required(VERSION 3.10)
project(imageBascis)

set(OpenCV_DIR /usr/local/lib)
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(imageBasics imageBasics.cpp)
target_link_libraries(imageBasics ${OpenCV_LIBS})

add_executable(undistortImage undistortImage.cpp)
target_link_libraries(undistortImage ${OpenCV_LIBS})

