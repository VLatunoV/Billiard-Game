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

add_subdirectory(Application)
add_subdirectory(Game)
add_subdirectory(Graphics)
add_subdirectory(Modules)
add_subdirectory(Physics)
add_subdirectory(Utils)
