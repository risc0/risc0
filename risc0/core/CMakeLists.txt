if (WIN32)
	set (PLATFORM_RNG rng_win32.cpp)
endif (WIN32)

if (APPLE)
	set (PLATFORM_RNG rng_macos.cpp)
endif (APPLE)

if (LINUX)
	set (PLATFORM_RNG rng_macos.cpp)
endif (LINUX)

add_library(core 
	log.cpp  
	elf.cpp  
	rng.cpp
	${PLATFORM_RNG}
)

add_subdirectory(test)

