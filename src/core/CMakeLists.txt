find_package(JUCE REQUIRED
	COMPONENTS
	juce_core
	juce_audio_processors
	juce_events
)

set(TARGET_NAME core)

file(GLOB SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS *.hpp)
add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})
add_library(CuteHost::Core ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${TARGET_NAME} PRIVATE
	${CMAKE_BINARY_DIR}
	${JUCE_INCLUDE_DIR}
	${VST_INCLUDE_DIR}
)

target_link_libraries(${TARGET_NAME} PUBLIC Qt5::Core)
target_link_libraries(${TARGET_NAME} PRIVATE ${JUCE_LIBRARIES})

if(UNIX)
	find_package(Freetype REQUIRED)
	find_package(PkgConfig REQUIRED)
	find_package(Threads REQUIRED)
	pkg_check_modules(GTK REQUIRED "gtk+-3.0")
	pkg_check_modules(WEBKIT REQUIRED "webkit2gtk-4.0")
	target_include_directories(${TARGET_NAME} PRIVATE
		${GTK_INCLUDE_DIRS}
		${WEBKIT_INCLUDE_DIRS}
	)
	target_link_libraries(${TARGET_NAME} PRIVATE
		Freetype::Freetype
		${GTK_LIBRARIES}
		${WEBKIT_LIBRARIES}
		Threads::Threads
		X11
		Xext
		curl
		dl
	)
endif()

target_compile_definitions(${TARGET_NAME}
	PRIVATE
	JUCE_WASAPI=1
	JUCE_DIRECTSOUND=1
	JUCE_ALSA=1
	JUCE_PLUGINHOST_VST=0
	JUCE_PLUGINHOST_VST3=1
	JUCE_PLUGINHOST_AU=0
	DONT_SET_USING_JUCE_NAMESPACE
)

if (MSVC)
	target_compile_options(${TARGET_NAME} PUBLIC /bigobj)
endif()
