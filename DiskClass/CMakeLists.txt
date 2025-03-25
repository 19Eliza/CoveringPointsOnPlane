cmake_minimum_required(VERSION 3.22)
project(DiskClass)

set(POINT_DIR /root/projects/CoveringPointOnPlane/PointClass/)

file(GLOB POINT_SRC "${POINT_DIR}/PointClass.h" "${POINT_DIR}/PointClass.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${POINT_SRC} DiskClass.h main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})