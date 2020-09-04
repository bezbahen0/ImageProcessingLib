cmake_minimum_required(VERSION 3.16.0)

project(ImageProcessingLib C CXX)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_subdirectory(test)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ImageProcessingLib ${HEADERS} ${SOURCES})
