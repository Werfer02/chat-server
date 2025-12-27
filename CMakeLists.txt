cmake_minimum_required(VERSION 3.30)
project(server VERSION 0.0.0 LANGUAGES C CXX)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(server server.cpp)
add_executable(client client.cpp)

target_include_directories(server PRIVATE
    "C:/Program Files/Boost/boost_1_90_0"
)

target_include_directories(client PRIVATE
    "C:/Program Files/Boost/boost_1_90_0"
)

target_link_libraries(server PRIVATE ws2_32)
target_link_libraries(client PRIVATE ws2_32)
