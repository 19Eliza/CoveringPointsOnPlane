cmake_minimum_required(VERSION 3.22)
project(CoverProblem)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(GeometryObjectsClass)
#add_subdirectory(GreedyAlgorithm)
add_subdirectory(RandomPoints)
add_subdirectory(ConvexHall)
add_subdirectory(Clusters)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(CoverProblem PRIVATE ClustersLib ConvexHallLib RandomPointsLib GeometryObjectsClassLib)
#target_link_libraries(${CMAKE_PROJECT_NAME} ConvexHallLib)
#target_link_libraries(${CMAKE_PROJECT_NAME} ClustersLib)



