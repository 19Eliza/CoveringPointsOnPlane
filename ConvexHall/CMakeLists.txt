cmake_minimum_required(VERSION 3.22)
project(ConvexHall)

file(GLOB PROJECT_SRC "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

set(POINTCLASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../PointClass)

include_directories(${POINTCLASS_DIR})

find_library(POINTCLASS_LIB NAMES PointClass PATHS ${POINTCLASS_DIR}/build)

if(POINTCLASS_LIB)
    message(STATUS "PointClass library found at: ${POINTCLASS_LIB}")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${POINTCLASS_LIB})
else()
    message(FATAL_ERROR "PointClass library not found! Make sure to build it first.")
endif()

add_library(ConvexHallLib STATIC ConvexHall.cpp)
target_include_directories(ConvexHallLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


