cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

add_library(filter STATIC filter.cpp)
target_include_directories(filter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})