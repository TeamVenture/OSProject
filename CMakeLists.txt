cmake_minimum_required(VERSION 3.2)
project(clion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES TestMain.cpp ReplacementStrategies.cpp ReferenceSet.cpp)
add_executable(clion ${SOURCE_FILES} TestMain.cpp)