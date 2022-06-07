if(ENABLE_TESTS)
	add_executable(
		fp4 
		fp4.cpp
	)
	target_link_libraries(fp4  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(fp4 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
	gtest_discover_tests(fp4)


        add_executable(
		fp
		fp.cpp
        )
        target_link_libraries(fp  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(fp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(fp)

        add_executable(
                core-ntt
                ntt.cpp
        )
        target_link_libraries(core-ntt  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(core-ntt PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(core-ntt)

        add_executable(
                sha256
                sha256.cpp
        )
        target_link_libraries(sha256  core zkp-core zkp-accel-backend-cpu zkp-accel-kernels ${GTEST_LIBS} )
        set_target_properties(sha256 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${GTEST_OUTPUT})
        gtest_discover_tests(sha256)

endif()
