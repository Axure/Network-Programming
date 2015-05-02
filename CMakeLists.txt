cmake_minimum_required(VERSION 3.1)
project(NetworkProgramming)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES)
add_executable(Server server.h server.cpp)
add_executable(Client client.h client.cpp)