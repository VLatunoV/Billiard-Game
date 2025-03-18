include(${CMAKE_SOURCE_DIR}/cmake/utilities.cmake)

set(APP_NAME app)

set(SOURCES main.cpp)

add_executable(${APP_NAME} ${SOURCES})

target_link_libraries(${APP_NAME}
	PRIVATE
		OpenGL::GL
		${IMGUI_NAME}
)

install_runtime_dependencies(${APP_NAME})
