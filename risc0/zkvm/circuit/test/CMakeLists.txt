if(ENABLE_TESTS)
	add_executable(
		risc0-simulate
		risc0-simulate.cpp
	)
	target_link_libraries(risc0-simulate  zkvm-prove zkp-accel-backend-cpu zkp-accel-kernels core zkp-core ${GTEST_LIBS} )
	set_target_properties(risc0-simulate PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
endif()
