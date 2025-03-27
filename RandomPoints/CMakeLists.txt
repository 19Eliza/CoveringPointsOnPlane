cmake_minimum_required(VERSION 3.22)
project(RandomPoints)

#set(POINT_DIR /root/projects/CoveringPointOnPlane/PointClass/)

set(POINTCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../PointClass)

include_directories(${POINTCLASS_DIR})

file(GLOB PROJECT_SRC "*.h" "*.cpp")

#file(GLOB POINT_SRC "${POINT_DIR}/PointClass.h" "${POINT_DIR}/PointClass.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SRC}) #${POINT_SRC})

find_library(POINTCLASS_LIB NAMES PointClass PATHS ${POINTCLASS_DIR}/build)

if(POINTCLASS_LIB)
    message(STATUS "PointClass library found at: ${POINTCLASS_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${POINTCLASS_LIB})
else()
    message(FATAL_ERROR "PointClass library not found! Make sure to build it first.")
endif()

#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})
