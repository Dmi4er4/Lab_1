cmake_minimum_required(VERSION 3.21)
project(lab_1)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(lab_1 traffic_manager.cpp traffic_manager.h traffic_manager_tests.cpp graph.cpp graph.h)
target_link_libraries(lab_1 gtest_main)