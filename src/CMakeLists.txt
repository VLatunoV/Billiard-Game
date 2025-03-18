include(${CMAKE_SOURCE_DIR}/cmake/utilities.cmake)

set(APP_TARGET_NAME app)

set(SOURCES main.cpp)

add_executable(${APP_TARGET_NAME} ${SOURCES})

set_target_properties(${APP_TARGET_NAME}
	PROPERTIES
		OUTPUT_NAME Billiards
)

target_link_libraries(${APP_TARGET_NAME}
	PRIVATE
		OpenGL::GL
		${IMGUI_NAME}
)

install_runtime_dependencies(${APP_TARGET_NAME})
