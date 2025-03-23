set(TARGET_NAME modules)

file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB HEADERS CONFIGURE_DEPENDS *.h)
file(GLOB INTERFACES CONFIGURE_DEPENDS interface/*.h)

source_group(Interfaces FILES ${INTERFACES})

add_library(${TARGET_NAME} STATIC
	${SOURCES}
	${HEADERS}
	${INTERFACES}
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
		imgui
	PRIVATE
		utils
)
