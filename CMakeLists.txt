cmake_minimum_required(VERSION 3.16.3)
project(risc0 LANGUAGES C CXX ASM)

include(ExternalProject)
include(FetchContent)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENABLE_TESTS ON)
set(BUILD_RISCVM ON)
set(BUILD_RISCVCROSS ON)
set(BUILD_EMBEDDED_RISC ON) #Will disable an embedded risc compilation

if(CMAKE_C_COMPILER MATCHES "risc")
  message ("Using a risc cross compile. Forcing risc only components.")
  set(BUILD_RISCVCROSS ON)
  set(ENABLE_TESTS OFF)
  set(BUILD_RISCVM OFF)
  set(BUILD_EMBEDDED_RISC OFF)
else()
  set(BUILD_RISCVCROSS OFF)
  if(BUILD_EMBEDDED_RISC)
    ExternalProject_Add(
      risc0_cross_riscv
      URL ""
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/risc0_cross
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
      CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/cmake/riscv.cmake
      INSTALL_COMMAND cmake -E echo "Skipping install step."
      BUILD_COMMAND make
      ALWAYS TRUE
    )
  endif()
  FetchContent_Declare(oneTBB
    GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
  )
  FetchContent_MakeAvailable(oneTBB)


endif()

include(cmake/CMakeConfig.txt)

set(CMAKE_CXX_STANDARD 17)
include_directories(${risc0_SOURCE_DIR} ${CMAKE_BINARY_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message("CMAKE_C_FLAGS:" ${CMAKE_C_FLAGS})
message("CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})
message("CMAKE_EXE_LINKER_FLAGS:" ${CMAKE_EXE_LINKER_FLAGS})

add_subdirectory(risc0)
add_subdirectory(examples)
