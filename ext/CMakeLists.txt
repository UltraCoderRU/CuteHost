# VST3 SDK
set(VST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vst3sdk CACHE PATH "VST SDK includes")

# NodeEditor
set(BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(nodeeditor)
