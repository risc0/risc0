

cmake ../risc0 -DCMAKE_TOOLCHAIN_FILE=../risc0/cmake/riscv.cmake

1. Compilation options:

	ENABLE_TESTS - will install Gtest and compile tests
	
1. OSX  RISC-V toolchain

Binary installation:
	brew tap riscv-software-src/riscv


To compile RISV toolchain following tools have to be installed
	brew install python3 gawk gnu-sed gmp mpfr libmpc isl zlib expat
	
