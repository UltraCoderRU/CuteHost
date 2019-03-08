set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(TARGET_NAME CuteHost)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)
file(GLOB_RECURSE RESOURCES *.qrc)

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${TARGET_NAME}
	CuteHost::Core
	NodeEditor::nodes
)
target_link_options(${TARGET_NAME} PRIVATE /IGNORE:4217)
