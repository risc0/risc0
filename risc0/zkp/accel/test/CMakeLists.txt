if(ENABLE_TESTS)
	add_executable(
		fp4_accel 
		fp4_accel.cpp
	)
	target_link_libraries(fp4_accel  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(fp4_accel PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
	gtest_discover_tests(fp4_accel)


        add_executable(
		fp_accel
		fp_accel.cpp
        )
        target_link_libraries(fp_accel  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(fp_accel PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(fp_accel)

        add_executable(
                ntt
                ntt.cpp
        )
        target_link_libraries(ntt  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(ntt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(ntt)


endif()
