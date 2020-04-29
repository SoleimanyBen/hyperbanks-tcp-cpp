# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("hyperbanks-tcp")

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost 1.73.0)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_definitions(-DCMAKE_BUILD_TYPE=Debug)

include_directories(libs/asio/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(hb-server 
    src/main.cpp
    src/server/HBServer.cpp
    src/server/HBServer.h
    src/server/HBSession.cpp
    src/server/HBSession.h
    src/enums/EPacketType.h
)

TARGET_LINK_LIBRARIES(hb-server LINK_PUBLIC ${Boost_LIBRARIES})