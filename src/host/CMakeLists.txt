set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(TARGET_NAME CuteHost)

set(APPLICATION_VERSION_MAJOR 0)
set(APPLICATION_VERSION_MINOR 1)
set(APPLICATION_VERSION ${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR})

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)
file(GLOB_RECURSE RESOURCES *.qrc)

if (WIN32)
	configure_file(appicon.rc.in ${CMAKE_CURRENT_BINARY_DIR}/appicon.rc)
	list(APPEND RESOURCES ${CMAKE_CURRENT_BINARY_DIR}/appicon.rc)
endif()

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(${TARGET_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})
else()
	add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})
endif()

target_link_libraries(${TARGET_NAME}
	CuteHost::Core
	NodeEditor::nodes
)
target_compile_definitions(${TARGET_NAME} PRIVATE CUTEHOST_APPLICATION_VERSION="${APPLICATION_VERSION}")

# Suppress warnings, when linking static NodeEditor
target_link_options(${TARGET_NAME} PRIVATE /IGNORE:4217,4049)
