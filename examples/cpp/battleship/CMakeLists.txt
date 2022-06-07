set (BATTLESHIP_OUTPUTDIR ${PROJECT_BINARY_DIR}/battleship)


if(BUILD_RISCVM)
	set (HOST_LIBS core zkp-prove zkp-accel-backend-cpu zkp-accel-kernels zkp-prove zkp-verify  zkvm-verify zkvm-prove zkvm-circuit zkp-core zkvm-r0vm zkvm-sdk-cpp-host )

	add_library(battleship-core
		core.cpp
		protocol.cpp
	)


	add_executable(battleship 
		battleship.cpp
	)

	target_link_libraries(battleship  battleship-core TBB::tbb  ${HOST_LIBS} )
	set_target_properties(battleship PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR})
endif()

if(BUILD_RISCVCROSS)
	add_executable(init_method init_method.cpp core.cpp)
	target_link_libraries(init_method zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)
	add_executable(turn_method turn_method.cpp core.cpp)
	target_link_libraries(turn_method zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)

	set_target_properties(init_method PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/)
	set_target_properties(turn_method PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/)

endif ()

if(ENABLE_TESTS AND BUILD_RISCVM)
        add_executable(
		battleship_test
                test.cpp
        )
        target_link_libraries(battleship_test  core battleship-core ${GTEST_LIBS} ${HOST_LIBS}  )
        set_target_properties(battleship_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR} ) 
        gtest_discover_tests(battleship_test)
endif()

