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
if (CMAKE_APPLE_SILICON_PROCESSOR)
  set(APPLE_M1_MONKEY 
    sed -i .bak "s/.*=host-darwin.o$//" riscv-gcc/gcc/config.host && sed -i .bak "s/.* x-darwin.$//" riscv-gcc/gcc/config.host && )
else()
  set(APPLE_M1_MONKEY )
endif()
    ExternalProject_Add(
      risc0_toolchain
      GIT_REPOSITORY "https://github.com/riscv/riscv-gnu-toolchain"
      UPDATE_COMMAND ""
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/risc0_toolchain	
      CONFIGURE_COMMAND ${APPLE_M1_MONKEY} ./configure  --with-arch=rv32im --with-abi=ilp32 --with-cmodel=medany --prefix=${CMAKE_CURRENT_BINARY_DIR}/riscv32-toolchain-bin
      BUILD_IN_SOURCE 1
      BUILD_COMMAND make -j 4
      INSTALL_COMMAND make install
    )

else()
  set(BUILD_RISCVCROSS OFF)
  if(BUILD_EMBEDDED_RISC)
    if (CMAKE_GENERATOR STREQUAL "Ninja")
      message ("Forcing a Ninja generator")
      set (GEN_FLAG "-G Ninja")
      set (GEN_BUILD "ninja")
    else()
      set (GEN_FLAG "")
      set (GEN_BUILD "make")
    endif()
    ExternalProject_Add(
      risc0_cross_riscv
      URL ""
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/risc0_cross
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
      CMAKE_ARGS ${GEN_FLAG} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/cmake/riscv.cmake
      INSTALL_COMMAND cmake -E echo "Skipping install step."
      BUILD_COMMAND ${GEN_BUILD}
      ALWAYS TRUE
      #To specify outputs is only Ninja specific deficiency
      BUILD_BYPRODUCTS risc0_cross/src/risc0_cross_riscv-build/bin/test_invalid_addr
                       risc0_cross/src/risc0_cross_riscv-build/bin/test_wom_same
                       risc0_cross/src/risc0_cross_riscv-build/bin/test_wom_diff
                       risc0_cross/src/risc0_cross_riscv-build/battleship/examples/cpp/battleship/init_method
                       risc0_cross/src/risc0_cross_riscv-build/battleship/examples/cpp/battleship/turn_method
                       risc0_cross/src/risc0_cross_riscv-build/deck/examples/cpp/deck/card_method
                       risc0_cross/src/risc0_cross_riscv-build/deck/examples/cpp/deck/shuffle_method
    )
  endif()
  FetchContent_Declare(oneTBB
    GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
  )
  set(TBB_TEST OFF CACHE BOOL "Switch off TBB Test build")
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
