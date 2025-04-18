cmake_minimum_required(VERSION 3.22)
project(CoverProblem)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_subdirectory(GeometryObjectsClass)
add_subdirectory(RandomPoints)
add_subdirectory(ConvexHall)
add_subdirectory(Clusters)
add_subdirectory(CoverAlgorithm)

add_executable(${CMAKE_PROJECT_NAME} main.cpp PointsWidget.cpp PointsWidget.h)

target_link_libraries(CoverProblem PRIVATE Qt5::Widgets GreedyAlgorithmLib ClustersLib ConvexHallLib RandomPointsLib GeometryObjectsClassLib)




