cmake_minimum_required(VERSION 3.13)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab4 main.cpp include/TreeNode.h include/BinTree.h src/TreeNode.cpp src/BinTree.cpp)