cmake_minimum_required(VERSION 3.22)
project(PointClass)

add_library(PointClass PointClass.cpp)
target_include_directories(PointClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})