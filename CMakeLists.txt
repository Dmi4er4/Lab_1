cmake_minimum_required(VERSION 3.21)
project(lab_1)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(lab_1 abstract_graph.h clique.cpp clique.h clique_tests.cpp chain.cpp chain.h chain_tests.cpp)
target_link_libraries(lab_1 gtest_main)