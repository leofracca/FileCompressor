cmake_minimum_required(VERSION 3.27)
project(fileCompressor)

set(CMAKE_CXX_STANDARD 20)

add_executable(fileCompressor src/main.cpp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

target_sources(fileCompressor PRIVATE ${SOURCES} ${HEADERS})

target_include_directories(fileCompressor PRIVATE src)
