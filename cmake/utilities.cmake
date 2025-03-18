function(install_runtime_dependencies TARGET_NAME)
	add_custom_command(
		TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
			-E copy_if_different
			"$<TARGET_RUNTIME_DLLS:${TARGET_NAME}>" # Source
			"$<TARGET_FILE_DIR:${TARGET_NAME}>" # Destination
		COMMENT "Copying dlls to build directory..." VERBATIM
	)
endfunction()
