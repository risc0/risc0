if(ENABLE_TESTS)
  set(TEST_LIBS
    zkp-core
    zkp-accel-backend-cpu
    zkp-accel-kernels
    core
  )
	
  FILE( GLOB local_tests *.cpp )
  FOREACH( testsource ${local_tests} )
    GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
    Add_risc0_test( "zkp-core" ${filename} "${TEST_LIBS}" )
  ENDFOREACH()
endif()
