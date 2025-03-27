cmake_minimum_required(VERSION 3.22)
project(GenerateClusters)

file(GLOB PROJECT_SRC "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

set(POINTCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../PointClass)
set(RANDOMPOINTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../RandomPoints)

include_directories(${POINTCLASS_DIR})
include_directories(${RANDOMPOINTS_DIR})

find_library(POINTCLASS_LIB NAMES PointClass PATHS ${POINTCLASS_DIR}/build)
find_library(RANDOMPOINTS_LIB NAMES RandomPointsLib PATHS ${RANDOMPOINTS_DIR}/build)

if(POINTCLASS_LIB)
    message(STATUS "PointClass library found at: ${POINTCLASS_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${POINTCLASS_LIB})
else()
    message(FATAL_ERROR "PointClass library not found! Make sure to build it first.")
endif()

if(RANDOMPOINTS_LIB)
    message(STATUS "RandomPoints library found at: ${RANDOMPOINTS_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${RANDOMPOINTS_LIB})
else()
    message(FATAL_ERROR "RandomPoints library not found! Make sure to build it first.")
endif()

add_library(ClustersLib STATIC GenerateClusters.cpp)
target_include_directories(ClustersLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ClustersLib PUBLIC RandomPointsLib)
