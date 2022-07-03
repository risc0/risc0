if(ENABLE_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker
  # settings
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
  set(GTEST_LIBS gtest gtest_main)
  set(GTEST_OUTPUT ${CMAKE_BINARY_DIR}/tests)
  macro(add_risc0_test_with_customdir test_prefix filename test_libs out_dir)
    message("Adding a test case:" ${filename} "  Libs:" ${test_libs} "workdir:"
            ${out_dir})
    add_executable(${test_prefix}-${filename} ${filename}.cpp)
    set_target_properties(${test_prefix}-${filename}
                          PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${out_dir})
    target_link_libraries(${test_prefix}-${filename} ${test_libs} ${GTEST_LIBS})
    add_test(
      NAME ${test_prefix}-${filename}
      WORKING_DIRECTORY ${out_dir}
      COMMAND $<TARGET_FILE:${test_prefix}-${filename}>)
    # Add a special test command with the depency to build test
    add_custom_target(test-${test_prefix}-${filename}
                      DEPENDS ${test_prefix}-${filename})
    add_custom_command(
      TARGET test-${test_prefix}-${filename}
      COMMAND ${CMAKE_CTEST_COMMAND} "-R ${test_prefix}-${filename}")
    add_dependencies(test-${test_prefix}-${filename} ${test_prefix}-${filename})
  endmacro(add_risc0_test_with_customdir)
  macro(add_risc0_test test_prefix filename test_libs)
    add_risc0_test_with_customdir(${test_prefix} ${filename} "${test_libs}"
                                  ${GTEST_OUTPUT})
  endmacro(add_risc0_test)

  enable_testing()
else()
  message(WARNING,"Google testing is disabled.")
endif()
