cmake_minimum_required(VERSION 3.0)

project(joinMap)

find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
#include_directories(${PROJECT_SOURCE_DIR}/include)


#find_package(Sophus REQUIRED)
#include_directories(${Sophus_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)
#include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(joinMap joinMap.cpp)
target_link_libraries(joinMap ${Pangolin_LIBRARIES} ${OpenCV_LIBS})
