cmake_minimum_required(VERSION 3.12)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3 main.cpp include/DoublyLinkedList.h src/DoublyLinkedList.cpp include/ListNode.h src/ListNode.cpp)