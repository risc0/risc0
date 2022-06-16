set(BATTLESHIP_OUTPUTDIR ${PROJECT_BINARY_DIR}/battleship)

if(BUILD_RISCVM)
  set(HOST_LIBS
    zkvm-circuit
    zkvm-sdk-cpp-host
    zkvm-prove
    zkvm-verify
    zkp-verify
    zkp-accel-backend-cpu
    zkp-prove
    zkp-core
    core
  )

  add_library(battleship-core
    core.cpp
    protocol.cpp
  )

  add_executable(battleship
    battleship.cpp
  )

  target_link_libraries(battleship battleship-core TBB::tbb ${HOST_LIBS})
  set_target_properties(battleship PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR})

  # Fetch methods built by an external project and render id file for both methods
  if(BUILD_EMBEDDED_RISC)
    message("Fetch from risc0_cross_riscv enabled.")
    risc0_fetch_cross_artifact(init_method
      ${PROJECT_BINARY_DIR}/risc0_cross/src/risc0_cross_riscv-build/battleship/examples/cpp/battleship/init_method
      ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/init_method
    )
    add_dependencies(init_method risc0_cross_riscv)

    risc0_fetch_cross_artifact(turn_method
      ${PROJECT_BINARY_DIR}/risc0_cross/src/risc0_cross_riscv-build/battleship/examples/cpp/battleship/turn_method
      ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/turn_method
    )
    add_dependencies(turn_method risc0_cross_riscv)
  else()
    message("Cross build for the methods is disabled memthods need to be provided manually.")
  endif()

  risc0_make_id("init_method.id" ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/init_method)
  risc0_make_id("turn_method.id" ${BATTLESHIP_OUTPUTDIR}/examples/cpp/battleship/turn_method)
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

  target_link_libraries(battleship_test core battleship-core ${GTEST_LIBS} ${HOST_LIBS})
  set_target_properties(battleship_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BATTLESHIP_OUTPUTDIR})
  gtest_discover_tests(battleship_test)
endif()

