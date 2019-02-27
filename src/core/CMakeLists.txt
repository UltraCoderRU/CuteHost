set(TARGET_NAME core)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)
add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC Qt5::Core)
