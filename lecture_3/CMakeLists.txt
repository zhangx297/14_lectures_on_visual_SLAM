cmake_minimum_required(VERSION 3.10)
project(eigenMatrix)
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )
add_executable(eigenMatrix visualizeGeometry.cpp)
target_link_libraries( eigenMatrix ${Pangolin_LIBRARIES} )








