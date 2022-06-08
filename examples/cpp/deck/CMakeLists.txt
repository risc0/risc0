set (DECK_OUTPUTDIR ${PROJECT_BINARY_DIR}/deck)

if(BUILD_RISCVCROSS)
	add_executable(card_method card_method.cpp)
	target_link_libraries(card_method zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)
        add_executable(shuffle_method deck.cpp shuffle_method.cpp)
        target_link_libraries(shuffle_method zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)

	set_target_properties(card_method PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DECK_OUTPUTDIR}/examples/cpp/deck/)
	set_target_properties(shuffle_method PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DECK_OUTPUTDIR}/examples/cpp/deck/)

endif ()

if(ENABLE_TESTS AND BUILD_RISCVM)
        set (HOST_LIBS core zkp-prove zkp-accel-backend-cpu zkp-accel-kernels zkp-prove zkp-verify  zkvm-verify zkvm-prove zkvm-circuit zkp-core zkvm-r0vm zkvm-sdk-cpp-host )
        add_executable(
		deck_test
                test.cpp
		protocol.cpp
        )
        target_link_libraries(deck_test  core ${GTEST_LIBS} ${HOST_LIBS}  )
        set_target_properties(deck_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DECK_OUTPUTDIR} ) 
        gtest_discover_tests(deck_test)


endif()

