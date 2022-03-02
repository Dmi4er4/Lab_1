cmake_minimum_required(VERSION 3.21)
project(lab_1)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined")
add_executable(lab_1 abstract_graph.h clique.cpp clique.h clique_tests.cpp chain.cpp chain.h
        chain_tests.cpp graph.h graph.cpp graph_tests.cpp traffic_manager.cpp traffic_manager.h
        traffic_manager_tests.cpp time_research.cpp)
add_executable(lab_1_traffic abstract_graph.h graph.h graph.cpp traffic_manager.cpp clique.h
        clique.cpp chain.h chain.cpp traffic_manager.h traffic_manager_tests.cpp)
target_link_libraries(lab_1 gtest_main)
target_link_libraries(lab_1_traffic gtest_main)
