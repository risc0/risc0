if(BUILD_RISCVM)
	set (HOST_LIBS core zkp-prove zkp-accel-backend-cpu zkp-accel-kernels zkp-prove zkp-verify  zkvm-verify zkvm-prove zkvm-circuit zkp-core zkvm-r0vm zkvm-sdk-cpp-host )

	add_executable(verify
		verify.cpp
	)

	target_link_libraries(verify  ${HOST_LIBS} )
endif()
