cmake_minimum_required(VERSION 3.5)
project(CuteHost)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SMTG_ADD_VST3_PLUGINS_SAMPLES OFF CACHE BOOL "")
set(SMTG_ADD_VST3_HOSTING_SAMPLES OFF CACHE BOOL "")
set(SMTG_VSTGUI_TOOLS OFF CACHE BOOL "")
#add_subdirectory(ext/vst3sdk)

find_package(Qt5 REQUIRED Core Gui Quick)

set(BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(ext/nodeeditor)

add_subdirectory(src)
