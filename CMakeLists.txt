cmake_minimum_required(VERSION 3.30)
project(chat-server VERSION 0.0.0 LANGUAGES C CXX)

add_executable(chat-server src/main.cpp
                           src/chat.cpp
                           src/client.cpp
                           src/server.cpp
                           src/util.cpp)

target_include_directories(chat-server PRIVATE include)

if (WIN32)
    if (NOT BOOST_ROOT)
        set(BOOST_ROOT "") # set your Boost install dir here, eg. "C:\Program Files\Boost\boost_1_90_0"
        if(NOT BOOST_ROOT)
            message(FATAL_ERROR "please set BOOST_ROOT to your Boost install dir")
        endif()
    endif()
    target_include_directories(chat-server PRIVATE ${BOOST_ROOT})
    target_link_libraries(chat-server PRIVATE ws2_32)
endif()
