include(${CMAKE_SOURCE_DIR}/cmake/utilities.cmake)

set(TARGET_NAME billiards)

add_executable(${TARGET_NAME} main.cpp)

set_target_properties(${TARGET_NAME}
	PROPERTIES
		OUTPUT_NAME Billiards
)

target_link_libraries(${TARGET_NAME}
	PRIVATE
		app
		physics
		graphics
		modules
)

install_runtime_dependencies(${TARGET_NAME})

add_subdirectory(application)
add_subdirectory(game)
add_subdirectory(graphics)
add_subdirectory(modules)
add_subdirectory(physics)
add_subdirectory(utils)
