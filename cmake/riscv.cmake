# Cross tooling definition file for the riscv targetted builds, it will use toolchain from the 
# RISCV_BINARY_DIR variable passed in, or if it is empty attempt to search toolchain in path.

if(NOT DEFINED RISCV_BINARY_DIR)
  set (RISCV_BINARY_DIR "")
endif()
if (RISCV_BINARY_DIR STREQUAL "")
  find_file(RISCV_BINARY "riscv32-unknown-elf-gcc" PATHS ENV INCLUDE)
  message ("Searching result for RISCV in PATH:" ${RISCV_BINARY})
  string(REGEX REPLACE "\-gcc" "-" CROSS_COMPILE ${RISCV_BINARY})
else ()
  set(CROSS_COMPILE ${RISCV_BINARY_DIR}/bin/riscv32-unknown-elf-)
endif()

message ("USING toolchain from:" ${CROSS_COMPILE})

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR rv32im)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_ASM_COMPILER {CROSS_COMPILE}gcc)
set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)
set(CMAKE_OBJCOPY ${CROSS_COMPILE}objcopy)
set(CMAKE_OBJDUMP ${CROSS_COMPILE}objdump)

set(CMAKE_C_FLAGS " -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=rv32im")
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}"
    CACHE STRING "")
set(CMAKE_CXX_FLAGS
    "${CMAKE_C_FLAGS}"
    CACHE STRING "")
set(CMAKE_ASM_FLAGS
    "${CMAKE_C_FLAGS}"
    CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -march=rv32im -nostartfiles")
