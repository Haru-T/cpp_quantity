cmake_minimum_required(VERSION 3.16)

project(cpp_quantity CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cpp_quantity INTERFACE)
target_include_directories(cpp_quantity INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
