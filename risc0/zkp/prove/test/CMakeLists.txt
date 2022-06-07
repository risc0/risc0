if(ENABLE_TESTS)
	add_executable(
		fri 
		fri.cpp
	)
	target_link_libraries(fri  zkp-verify core zkp-prove zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(fri PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
	gtest_discover_tests(fri)


        add_executable(
		merkle
		merkle
        )
        target_link_libraries(merkle zkp-verify core zkp-prove zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(merkle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(merkle)

endif()
