if(ENABLE_TESTS)
  set(TEST_LIBS
    core
  )

  set (local_tests "archive.cpp")
  FOREACH( testsource ${local_tests} )
    GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
    Add_risc0_test( "risc0-core" ${filename} "${TEST_LIBS}" )
  ENDFOREACH()

endif()
