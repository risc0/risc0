if(ENABLE_TESTS)
  set(TEST_LIBS
    zkp-verify
    core
    zkp-accel-backend-cpu
    zkp-accel-kernels
    zkp-prove
    zkp-core
  )
	
  FILE( GLOB local_tests *.cpp )
  FOREACH( testsource ${local_tests} )
    GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
    Add_risc0_test("zkp-prove" "${filename}" "${TEST_LIBS}")
  ENDFOREACH()
endif()
