set(IMGUI_NAME imgui)

file(GLOB SOURCES
	${CMAKE_SOURCE_DIR}/3rd/imgui/*.cpp
	${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.cpp
)

file(GLOB HEADERS
	${CMAKE_SOURCE_DIR}/3rd/imgui/*.h
	${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.h
)

add_library(${IMGUI_NAME} STATIC
	${SOURCES}
	${HEADERS}
)

target_include_directories(${IMGUI_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/3rd/imgui
		${CMAKE_SOURCE_DIR}/3rd/imgui/backends
)
