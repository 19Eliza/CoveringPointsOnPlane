cmake_minimum_required(VERSION 3.22)
project(GenerateClUsters)

set(POINT_DIR /root/projects/CoveringPointOnPlane/PointClass/)
#set(DISK_DIR /root/projects/CoveringPointOnPlane/DiskClass/)
set(RANDOMPOINTS_DIR /root/projects/CoveringPointOnPlane/RandomPoints/)

file(GLOB POINT_SRC "${POINT_DIR}/PointClass.h" "${POINT_DIR}/PointClass.cpp")
#file(GLOB DISK_SRC "${DISK_DIR}/DiskClass.h" "${DISK_DIR}/DiskClass.cpp")
file(GLOB RANDOMPOINTS_SRC "${RANDOMPOINTS_DIR}/RandomPoints.h" "${RANDOMPOINTS_DIR}/RandomPoints.cpp")
file(GLOB PROJECT_SRC "*.cpp" "*.h")

add_executable(${CMAKE_PROJECT_NAME}  ${PROJECT_SRC} ${POINT_SRC}  ${RANDOMPOINTS_SRC}) #${DISK_SRC}

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})
#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${DISK_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${RANDOMPOINTS_DIR})