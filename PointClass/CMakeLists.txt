cmake_minimum_required(VERSION 3.22)
project(PointClass)

add_library(${PROJECT_NAME} STATIC PointClass.cpp)
 
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})