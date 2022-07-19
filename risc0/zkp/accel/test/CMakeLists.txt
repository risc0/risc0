if(ENABLE_TESTS)
  set(TEST_LIBS
    core 
    zkp-accel-backend-cpu 
    zkp-accel-kernels 
    zkp-core
  )

  FILE(GLOB local_tests *.cpp)
  FOREACH(testsource ${local_tests})
    GET_FILENAME_COMPONENT(filename ${testsource} NAME_WE)
    add_risc0_test("zkp-accel" ${filename} "${TEST_LIBS}")
  ENDFOREACH()
endif()
