set(TARGET_NAME game)

file(GLOB SOURCES CONFIGURE_DEPENDS
	*.cpp
	Object/*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS
	*.h
	Object/*.h
)

add_library(${TARGET_NAME} STATIC
	${SOURCES}
	${HEADERS}
)
