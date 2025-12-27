cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing download step for boost")

block(SCOPE_FOR VARIABLES)

include("/home/Jacek/Projects/server/build/CMakeFiles/fc-stamp/boost/download-boost.cmake")
include("/home/Jacek/Projects/server/build/CMakeFiles/fc-stamp/boost/verify-boost.cmake")
include("/home/Jacek/Projects/server/build/CMakeFiles/fc-stamp/boost/extract-boost.cmake")


endblock()
