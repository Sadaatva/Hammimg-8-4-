cmake_minimum_required(VERSION 3.10)
project(hamming)
add_executable(hamming main.cpp)
target_link_libraries(hamming gtest)