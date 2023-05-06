cmake_minimum_required(VERSION 3.24)
project(AliansIT)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

add_executable(task1 task1/main.cpp)
add_executable(task2 task2/main.cpp task2/CompareInteractor.cpp task2/IStreamReadlineIterator.cpp)
