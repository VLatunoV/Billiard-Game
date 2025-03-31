set(TARGET_NAME game)

file(GLOB SOURCES CONFIGURE_DEPENDS
	*.cpp
	object/*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS
	*.h
	object/*.h
)

add_library(${TARGET_NAME} STATIC
	${SOURCES}
	${HEADERS}
)
