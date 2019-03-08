cmake_minimum_required(VERSION 3.5)
project(CuteHost)

if(POLICY CMP0071)
	set(CMAKE_POLICY_DEFAULT_CMP0071 OLD)
endif()

if(POLICY CMP0074)
	set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

if (MSVC)
	# NodeEditor adds /W4 to CXX_FLAGS, but CMake adds /W3 by default for MSVC, so we have warning D9025
	string(REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	string(REGEX REPLACE "-W3" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	add_definitions(/MP)
endif()

# Build external libraries
add_subdirectory(ext)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/ext/juce-cmake/cmake)

find_package(Qt5 REQUIRED Core Gui Quick)

# Build CuteHost sources
add_subdirectory(src)
