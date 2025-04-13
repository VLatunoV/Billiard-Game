set(TARGET_NAME graphics)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.h)

add_library(${TARGET_NAME} STATIC
	${SOURCES}
	${HEADERS}
)

target_link_libraries(${TARGET_NAME}
	PRIVATE
		OpenGL::GL
		imgui
		utils
)
