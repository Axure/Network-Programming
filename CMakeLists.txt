cmake_minimum_required(VERSION 3.1)
project(NetworkProgramming)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES)
add_executable(Server server.h server.cpp)
add_executable(Client client.h client.cpp)

add_executable(Chat_Server chat_server.cpp chat_message.hpp)
add_executable(Chat_Client chat_client.cpp chat_message.hpp)

set_target_properties(Chat_Server PROPERTIES LINK_FLAGS "-lboost_system")
set_target_properties(Chat_Client PROPERTIES LINK_FLAGS "-lboost_system")