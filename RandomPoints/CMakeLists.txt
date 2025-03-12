cmake_minimum_required(VERSION 3.22)
project(RandomPoints)

set(POINT_DIR /root/projects/CoveringPointOnPlane/Class/)

file(GLOB PROJECT_SRC "*.h" "*.cpp")
file(GLOB POINT_SRC "${POINT_DIR}/Class.h" "${POINT_DIR}/Class.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SRC} ${POINT_SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})
