include(${CMAKE_SOURCE_DIR}/cmake/utilities.cmake)

set(APP_TARGET_NAME app)

file(GLOB SOURCES CONFIGURE_DEPENDS
	*.cpp
)

file(GLOB HEADERS CONFIGURE_DEPENDS
	*.h
)

add_executable(${APP_TARGET_NAME} ${SOURCES} ${HEADERS})

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
