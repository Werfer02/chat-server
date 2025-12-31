cmake_minimum_required(VERSION 3.30)
project(chat-server VERSION 0.0.0 LANGUAGES C CXX)

add_executable(chat-server src/main.cpp
                           src/chat.cpp
                           src/client.cpp
                           src/server.cpp
                           src/util.cpp)

target_include_directories(chat-server PRIVATE include)

find_package(Boost REQUIRED)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found! Please set Boost_DIR or install Boost.")
endif()

target_include_directories(chat-server PRIVATE ${Boost_INCLUDE_DIRS})


if (WIN32)
    target_link_libraries(chat-server PRIVATE ws2_32 ${Boost_LIBRARIES})
endif()
