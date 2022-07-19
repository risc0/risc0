if(ENABLE_TESTS)
  set(TEST_LIBS
    zkvm-prove 
    core 
    zkp-core 
    zkp-accel-backend-cpu 
    zkp-accel-kernels
  )

  Add_risc0_test( "zkvm-prove" hw "${TEST_LIBS}" )

  if(BUILD_EMBEDDED_RISC)
    risc0_fetch_cross_artifact(test_invalid_addr
      ${PROJECT_BINARY_DIR}/risc0_cross_riscv/src/risc0_cross_riscv-build/bin/test_invalid_addr
      ${PROJECT_BINARY_DIR}/tests/risc0/zkvm/prove/test/test_invalid_addr
    )
    add_dependencies(test_invalid_addr risc0_cross_riscv)

    risc0_fetch_cross_artifact(test_wom_same
      ${PROJECT_BINARY_DIR}/risc0_cross_riscv/src/risc0_cross_riscv-build/bin/test_wom_same
      ${PROJECT_BINARY_DIR}/tests/risc0/zkvm/prove/test/test_wom_same
    )
    add_dependencies(test_wom_same risc0_cross_riscv)

    risc0_fetch_cross_artifact(test_wom_diff
      ${PROJECT_BINARY_DIR}/risc0_cross_riscv/src/risc0_cross_riscv-build/bin/test_wom_diff
      ${PROJECT_BINARY_DIR}/tests/risc0/zkvm/prove/test/test_wom_diff
    )
    add_dependencies(test_wom_diff risc0_cross_riscv)
  else()
     message("Cross build for the methods is disabled memthods need to be provided manually.")
  endif()

endif()

if(BUILD_RISCVCROSS)
  add_executable(test_invalid_addr test_invalid_addr.cpp)
  target_link_libraries(test_invalid_addr zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)

  add_executable(test_wom_diff test_wom_diff.cpp)
  target_link_libraries(test_wom_diff zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)

  add_executable(test_wom_same test_wom_same.cpp)
  target_link_libraries(test_wom_same zkvm-sdk-cpp-guest zkvm-sdk-cpp-guest-crt0)
endif ()

