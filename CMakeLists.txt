cmake_minimum_required(VERSION 3.17)
project(Tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tree main.cpp BinTree.h catch.hpp Tests.cpp Menu.h PerfomanceTest.h Menu.cpp PerfomanceTest.cpp Branch.h FromStringToTree.h)