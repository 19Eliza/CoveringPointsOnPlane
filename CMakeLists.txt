cmake_minimum_required(VERSION 3.22)
project(CoverProblem)

add_subdirectory(PointClass)
#add_subdirectory(GreedyAlgorithm)
add_subdirectory(RandomPoints)
add_subdirectory(Clusters)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PointClass)
target_link_libraries(${CMAKE_PROJECT_NAME} RandomPointsLib)
target_link_libraries(${CMAKE_PROJECT_NAME} ClustersLib)




