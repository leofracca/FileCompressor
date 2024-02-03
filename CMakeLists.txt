cmake_minimum_required(VERSION 3.27)
project(fileCompressor)

set(CMAKE_CXX_STANDARD 20)

add_executable(fileCompressor src/main.cpp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

target_sources(fileCompressor PRIVATE ${SOURCES} ${HEADERS})
target_sources(fileCompressor PRIVATE ${PROJECT_SOURCE_DIR}/utils/arguments.cpp ${PROJECT_SOURCE_DIR}/utils/arguments.h)

target_include_directories(fileCompressor PRIVATE src)
target_include_directories(fileCompressor PRIVATE utils)

# Boost
find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(fileCompressor PRIVATE Boost::program_options)

# Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/docs)

    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
    )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
