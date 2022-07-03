
if (BUILD_RISCVTOOLCHAIN)
  message ("Building risv toolchain internally.")

  if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL  Darwin AND ${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL arm64)
    set(APPLE_M1_MONKEY
      sed -i .bak "s/.*=host-darwin.o$//" riscv-gcc/gcc/config.host && sed -i .bak "s/.* x-darwin.$//" riscv-gcc/gcc/config.host && )
  else()
    set(APPLE_M1_MONKEY )
  endif()
  ExternalProject_Add(
    riscv_toolchain
    GIT_REPOSITORY "https://github.com/riscv/riscv-gnu-toolchain"
    UPDATE_COMMAND ""
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/risc0_toolchain
    CONFIGURE_COMMAND ${APPLE_M1_MONKEY} ./configure  --with-arch=rv32im --with-abi=ilp32 --with-cmodel=medany --prefix=${CMAKE_CURRENT_BINARY_DIR}/riscv-toolchain-bin
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -j 4
    INSTALL_COMMAND make install
)
else ()
  message ("RISCV toolachain internal build is disabled, expecting tooling in the PATH variable.")
  add_custom_target(riscv_toolchain ALL)
endif()
