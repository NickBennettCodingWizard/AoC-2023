cmake_minimum_required(VERSION 3.0...3.5)

# Must be done before the first call to project()
# https://github.com/Microsoft/vcpkg#vcpkg-with-visual-studio-cmake-projects
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Save on initial build time by only building vcpkg packages in release.
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/triplets")

# TODO: Make a variable to describe the year?
project(AOC CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "/Zi /Od")
    set(CMAKE_CXX_FLAGS_RELEASE_INIT "/O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")
endif()

include_directories(src)

# Generate a file that allows source code to use paths in the project like "inputs".
get_filename_component(INPUT_FILE_PATH "inputs" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOLUTIONS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/solutions")
configure_file(src/InputDirectoryConfig.cpp.in ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.cpp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(AOC_SOURCE_H
    src/ACSolver.ipp
    src/Utilities.ipp
    src/InputDirectoryConfig.hpp
)

set(AOC_SOURCE
    src/Utilities.cpp
    ${CMAKE_BINARY_DIR}/generated/InputDirectoryConfig.cpp
)

add_library(AOC STATIC
    ${AOC_SOURCE_H}
    ${AOC_SOURCE}
)

find_package(CURL CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
add_executable(StartNewDay src/StartNewDay.cpp src/HttpsRequest.cpp src/HttpsRequest.hpp)
target_link_libraries(StartNewDay PRIVATE CURL::libcurl cxxopts::cxxopts AOC)

if(MSVC)
    set(WINDOWS_VCPKG_BIN_RELEASE ${VCPKG_INSTALLED_DIR}/x64-windows/bin)
    set(WINDOWS_VCPKG_BIN_DEBUG ${VCPKG_INSTALLED_DIR}/x64-windows/debug/bin)

    file(COPY ${WINDOWS_VCPKG_BIN_RELEASE}/libcurl.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
    file(COPY ${WINDOWS_VCPKG_BIN_DEBUG}/libcurl-d.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

    file(COPY ${WINDOWS_VCPKG_BIN_RELEASE}/gtest.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
    file(COPY ${WINDOWS_VCPKG_BIN_DEBUG}/gtest.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

    file(COPY ${WINDOWS_VCPKG_BIN_RELEASE}/zlib1.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
    file(COPY ${WINDOWS_VCPKG_BIN_DEBUG}/zlibd1.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(AOC PROPERTIES FOLDER "Utilities")
    set_target_properties(StartNewDay PROPERTIES FOLDER "Utilities")
endif()

enable_testing()
find_package(GTest CONFIG REQUIRED)
add_subdirectory(solutions)
