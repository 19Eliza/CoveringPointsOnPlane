cmake_minimum_required(VERSION 3.22)
project(GeometryObjectsClass)

file(GLOB PROJECT_SRC "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

add_library(GeometryObjectsClassLib STATIC GeometryObjectsClass.cpp)
 
target_include_directories(GeometryObjectsClassLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})