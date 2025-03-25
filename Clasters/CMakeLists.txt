cmake_minimum_required(VERSION 3.22)
project(GenerateClasters)

set(POINT_DIR /root/projects/CoveringPointOnPlane/PointClass/)
set(DISK_DIR /root/projects/CoveringPointOnPlane/DiskClass/)
set(RANDOMPOINTS_DIR /root/projects/CoveringPointOnPlane/RandomPoints/)

file(GLOB POINT_SRC "${POINT_DIR}/PointClass.h" "${POINT_DIR}/PointClass.cpp")
file(GLOB DISK_SRC "${DISK_DIR}/DiskClass.h" "${DISK_DIR}/DiskClass.cpp")
file(GLOB DISK_SRC "${RANDOMPOINTS_DIR}/RandomPoints.h" "${RANDOMPOINTS_DIR}/RandomPoints.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${POINT_SRC} ${DISK_SRC} ${ANDOMPOINTS_DIR} GenerateClasters.h GenerateClasters.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${DISK_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${RANDOMPOINTS_DIR})