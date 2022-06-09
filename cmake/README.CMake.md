CMake build process.
--------------------

CMake is used to build tools test and risc ELF from the VM.  
CMake will assume that the RISC toolset is installed and available in PATH
It is also possible to configure a tree only for the risc code or only for VM


To compile methods using a compiler available in PATH variable:
	cmake ../risc0 -DCMAKE_TOOLCHAIN_FILE=../risc0/cmake/riscv.cmake

General settings
----------------
	ENABLE_TESTS         - will install Gtest and compile tests
	BUILD_RISCVM         - will build native set
	BUILD_CROSS_RISC     - will also compile methods via cross 
	BUILD_EMBEDDED_RISC  - will compile methods as a part of the single tree

RISC-V toolchain
----------------

git clone https://github.com/riscv/riscv-gnu-toolchain -b 2022.02.25
cd riscv-gnu-toolchain
# needed for Apple Silicon support
sed -i .bak 's/.*=host-darwin.o$//' riscv-gcc/gcc/config.host
sed -i .bak 's/.* x-darwin.$//' riscv-gcc/gcc/config.host
./configure \
  --prefix=/tmp/riscv32im-darwin-arm64 \
  --with-arch=rv32im \
  --with-abi=ilp32 \
  --with-cmodel=medany

