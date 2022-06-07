if(ENABLE_TESTS)
        add_executable(
                hw
                hw.cpp
        )
        target_link_libraries(hw  zkvm-prove core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(hw PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(hw)

	add_executable(
		test_invalid_addr 
		test_invalid_addr.cpp
	)
	target_link_libraries(test_invalid_addr  zkvm-prove core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(test_invalid_addr PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
	gtest_discover_tests(test_invalid_addr)


        add_executable(
		test_wom_diff
		test_wom_diff.cpp
        )
        target_link_libraries(test_wom_diff  zkvm-prove core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(test_wom_diff PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(test_wom_diff)

        add_executable(
                test_wom_same
                test_wom_same.cpp
        )
        target_link_libraries(test_wom_same  zkvm-prove core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(test_wom_same PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(test_wom_same)

endif()
