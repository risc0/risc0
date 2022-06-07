if(ENABLE_TESTS)
	add_executable(
		archive 
		archive.cpp
	)

	target_link_libraries(archive  core ${GTEST_LIBS} )
        set_target_properties(archive PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
	gtest_discover_tests(archive)
endif()
