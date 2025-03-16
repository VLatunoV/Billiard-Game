set(APP_NAME app)

set(SOURCES main.cpp)

add_executable(${APP_NAME} ${SOURCES})

target_link_libraries(${APP_NAME}
	PRIVATE
		OpenGL::GL
		${IMGUI_NAME}
)

add_custom_command(TARGET ${APP_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"$<TARGET_RUNTIME_DLLS:${APP_NAME}>" # Source
	"$<TARGET_FILE_DIR:${APP_NAME}>" # Destination
	COMMENT "Copying dlls to build directory..."
	VERBATIM
)
