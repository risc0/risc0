#include(CMakeForceCompiler)

# usage
# cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/rv32imac.cmake ../

# Look for GCC in path
# https://xpack.github.io/riscv-none-embed-gcc/
FIND_FILE( RISCV_XPACK_GCC_COMPILER_EXE "riscv-none-embed-gcc.exe" PATHS ENV INCLUDE)
FIND_FILE( RISCV_XPACK_GCC_COMPILER "riscv-none-embed-gcc" PATHS ENV INCLUDE)

# Look for RISC-V github GCC
# https://github.com/riscv/riscv-gnu-toolchain
FIND_FILE( RISCV_XPACK_GCC_COMPILER_EXT "riscv32-unknown-elf-gcc.exe" PATHS ENV INCLUDE)
FIND_FILE( RISCV_XPACK_GCC_COMPILER "riscv32-unknown-elf-gcc" PATHS ENV INCLUDE)

# Select which is found
if (EXISTS ${RISCV_XPACK_GCC_COMPILER})
set( RISCV_GCC_COMPILER ${RISCV_XPACK_GCC_COMPILER})
elseif (EXISTS ${RISCV_XPACK_GCC_COMPILER_EXE})
set( RISCV_GCC_COMPILER ${RISCV_XPACK_GCC_COMPILER_EXE})
elseif (EXISTS ${RISCV_GITHUB_GCC_COMPILER})
set( RISCV_GCC_COMPILER ${RISCV_GITHUB_GCC_COMPILER})
elseif (EXISTS ${RISCV_GITHUB_GCC_COMPILER_EXE})
set( RISCV_GCC_COMPILER ${RISCV_GITHUB_GCC_COMPILER_EXE})
else()
message(FATAL_ERROR "RISC-V GCC not found. ${RISCV_GITHUB_GCC_COMPILER} ${RISCV_XPACK_GCC_COMPILER} ${RISCV_GITHUB_GCC_COMPILER_EXE} ${RISCV_XPACK_GCC_COMPILER_EXE}")
endif()

message( "RISC-V GCC found: ${RISCV_GCC_COMPILER}")

get_filename_component(RISCV_TOOLCHAIN_BIN_PATH ${RISCV_GCC_COMPILER} DIRECTORY)
get_filename_component(RISCV_TOOLCHAIN_BIN_GCC ${RISCV_GCC_COMPILER} NAME_WE)
get_filename_component(RISCV_TOOLCHAIN_BIN_EXT ${RISCV_GCC_COMPILER} EXT)

message( "RISC-V GCC Path: ${RISCV_TOOLCHAIN_BIN_PATH}" )

STRING(REGEX REPLACE "\-gcc" "-" CROSS_COMPILE ${RISCV_TOOLCHAIN_BIN_GCC})
message( "RISC-V Cross Compile: ${CROSS_COMPILE}" )

# The Generic system name is used for embedded targets (targets without OS) in
# CMake
set( CMAKE_SYSTEM_NAME          Generic )
set( CMAKE_SYSTEM_PROCESSOR     rv32imac )
set( CMAKE_EXECUTABLE_SUFFIX    ".elf")

# specify the cross compiler. We force the compiler so that CMake doesn't
# attempt to build a simple test program as this will fail without us using
# the -nostartfiles option on the command line
#CMAKE_FORCE_C_COMPILER( "${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}gcc${RISCV_TOOLCHAIN_BIN_EXT}" GNU )
#CMAKE_FORCE_CXX_COMPILER( "${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}g++${RISCV_TOOLCHAIN_BIN_EXT}" GNU )
set(CMAKE_ASM_COMPILER {CROSS_COMPILE}gcc )
set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)

# We must set the OBJCOPY setting into cache so that it's available to the
# whole project. Otherwise, this does not get set into the CACHE and therefore
# the build doesn't know what the OBJCOPY filepath is
set( CMAKE_OBJCOPY      ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objcopy
     CACHE FILEPATH "The toolchain objcopy command " FORCE )

set( CMAKE_OBJDUMP      ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objdump
     CACHE FILEPATH "The toolchain objdump command " FORCE )

# Set the common build flags
# Set the CMAKE C flags (which should also be used by the assembler!
set( CMAKE_C_FLAGS " -g" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=rv32im" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
set( CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" )
set( CMAKE_EXE_LINKER_FLAGS   "${CMAKE_EXE_LINKER_FLAGS}  -march=rv32im    -nostartfiles   " )
