cmake_minimum_required(VERSION 3.30)
project(chat-server VERSION 0.0.0 LANGUAGES C CXX)

add_executable(chat-server main.cpp chat.cpp client.cpp server.cpp util.cpp)

target_include_directories(chat-server PRIVATE include)

if (WIN32)
    target_link_libraries(server PRIVATE ws2_32)
    target_link_libraries(client PRIVATE ws2_32)
endif()
