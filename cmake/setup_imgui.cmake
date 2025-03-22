set(IMGUI_TARGET imgui)

file(GLOB SOURCES
	${CMAKE_SOURCE_DIR}/3rd/imgui/*.cpp
	${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl3.cpp
	${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_opengl3.cpp
	${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.cpp
)

file(GLOB HEADERS
	${CMAKE_SOURCE_DIR}/3rd/imgui/*.h
	${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_sdl3.h
	${CMAKE_SOURCE_DIR}/3rd/imgui/backends/imgui_impl_opengl3.h
	${CMAKE_SOURCE_DIR}/3rd/imgui/misc/cpp/imgui_stdlib.h
)

add_library(${IMGUI_TARGET} STATIC
	${SOURCES}
	${HEADERS}
)

target_include_directories(${IMGUI_TARGET}
	PUBLIC
		${CMAKE_SOURCE_DIR}/3rd/imgui
		${CMAKE_SOURCE_DIR}/3rd/imgui/backends
)

target_link_libraries(${IMGUI_TARGET}
	PUBLIC
		SDL3::SDL3
)
