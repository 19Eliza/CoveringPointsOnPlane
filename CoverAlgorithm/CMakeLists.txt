cmake_minimum_required(VERSION 3.22)
project(GreedyAlgorithm)

file(GLOB PROJECT_SRC "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

set(GEOMETRYOBJECTSCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../GeometryObjectsClass)

include_directories(${GEOMETRYOBJECTSCLASS_DIR})

find_library(GEOMETRYOBJECTSCLASS_LIB NAMES GeometryObjectsClassLib PATHS ${GEOMETRYOBJECTSCLASS_DIR}/build)

if(GEOMETRYOBJECTSCLASS_LIB)
    message(STATUS "GeometryObjectsClass library found at: ${GEOMETRYOBJECTSCLASS_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GEOMETRYOBJECTSCLASS_LIB})
else()
    message(FATAL_ERROR "GeometryObjectsClass library not found! Make sure to build it first.")
endif()

add_library(GreedyAlgorithmLib STATIC CoverAlgorithm.cpp)
target_include_directories(GreedyAlgorithmLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

