cmake_minimum_required(VERSION 3.22)
project(RandomPoints)

#set(POINT_DIR /root/projects/CoveringPointOnPlane/PointClass/)

file(GLOB PROJECT_SRC "*.h" "*.cpp")

#file(GLOB POINT_SRC "${POINT_DIR}/PointClass.h" "${POINT_DIR}/PointClass.cpp")


add_executable(${PROJECT_NAME} ${PROJECT_SRC}) #${POINT_SRC})

#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${POINT_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE PointClass)