if(BUILD_RISCVCROSS)
	add_library(zkvm-sdk-cpp-guest
		cppstd.cpp 
		env.cpp    
		fail.cpp   
		key.cpp    
		prng.cpp   
		sha.cpp    
		stdlib.cpp 
		string.cpp
		memcpy.s
		memset.s
	)
        
	add_library(zkvm-sdk-cpp-guest-crt0
		crt0.s
	)
endif()
