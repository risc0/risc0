if (WIN32)
  set(PLATFORM_RNG rng_win32.cpp)
endif(WIN32)


if (UNIX AND APPLE)
  set (PLATFORM_RNG rng_macos.cpp)
endif ()

if (UNIX AND NOT APPLE)
  set (PLATFORM_RNG rng_linux.cpp)
endif ()

add_library(core
  util.cpp
  log.cpp
  elf.cpp
  rng.cpp
  ${PLATFORM_RNG}
)

add_dependencies (core riscv_toolchain) #Required for the parallel builds
add_subdirectory(test)
