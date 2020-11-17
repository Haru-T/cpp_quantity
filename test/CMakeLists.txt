cmake_minimum_required(VERSION 3.16)

project(${CMAKE_PROJECT_NAME}_tests CXX)
set(CMAKE_CXX_STANDARD 20)

# prepare Catch2 unit testing framework
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.3
)
FetchContent_MakeAvailable(Catch2)
set(CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib ${CMAKE_MODULE_PATH})

add_executable(test it_works.cpp)
target_link_libraries(test
    PRIVATE Catch2::Catch2
    INTERFACE cpp_quantity)

if (ENABLE_COVERAGE)
    FetchContent_Declare(
        CMake_codecov
        GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov
        GIT_TAG 39784bad607975ee91ca7c578fe5669563cd4c50
    )
    set(CMAKE_MODULE_PATH ${FETCHCONTENT_BASE_DIR}/cmake_codecov-src/cmake ${CMAKE_MODULE_PATH})
    FetchContent_MakeAvailable(CMake_codecov)

    find_package(codecov)
    add_coverage(test)
    list(APPEND LCOV_REMOVE_PATTERNS "/usr/")
    coverage_evaluate()
endif()

include(CTest)
include(Catch)
catch_discover_tests(test)