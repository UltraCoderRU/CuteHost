set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(TARGET_NAME CuteHost)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${TARGET_NAME}
	CuteHost::Core
	NodeEditor::nodes
)
