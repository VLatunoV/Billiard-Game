cmake_minimum_required(VERSION 3.29)

project(BilliardGame
	LANGUAGES CXX
	VERSION 0.0.0
)

include(cmake/setup_project.cmake)

add_subdirectory(app)
