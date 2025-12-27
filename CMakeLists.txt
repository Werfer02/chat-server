cmake_minimum_required(VERSION 3.30)
project(server VERSION 0.0.0 LANGUAGES C CXX)

find_package(Boost REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)
