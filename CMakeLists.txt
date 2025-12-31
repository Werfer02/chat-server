cmake_minimum_required(VERSION 3.30)
project(chat-server VERSION 0.0.0 LANGUAGES C CXX)

add_executable(chat-server src/main.cpp
                           src/chat.cpp
                           src/client.cpp
                           src/server.cpp
                           src/util.cpp)

target_include_directories(chat-server PRIVATE include)

if (WIN32)
    target_link_libraries(chat-server PRIVATE ws2_32)
endif()
