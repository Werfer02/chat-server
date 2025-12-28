cmake_minimum_required(VERSION 3.30)
project(server VERSION 0.0.0 LANGUAGES C CXX)

add_executable(server server.cpp)
add_executable(client client.cpp)

if (WIN32)
    target_link_libraries(server PRIVATE ws2_32)
    target_link_libraries(client PRIVATE ws2_32)
endif()
