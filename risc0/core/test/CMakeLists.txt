if(ENABLE_TESTS)
        #FILE( GLOB local_tests *.cpp )
	set (local_tests "archive.cpp")
        FOREACH( testsource ${local_tests} )
                GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
                Add_risc0_test( "risc0-core" ${filename} "zkvm-prove core zkp-core zkp-accel-backend-cpu zkp-accel-kernels" )
        ENDFOREACH()

endif()
