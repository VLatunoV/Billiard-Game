set(APP_NAME app)

set(SOURCES main.cpp)

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME}
	PRIVATE
		${IMGUI_NAME}
)
