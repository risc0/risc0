CMake build process.
--------------------

CMake is used to build a full set of c++ code.
CMake will install riscv toolchain as part of build process if it is not available in the path.
Building riscv toolchain internally is very slow and for faster builds PATH variable can include
binaries for the riscv toolchain ie:

export PATH=$PATH:/opt/riscv32/bin 


Full compilation
-----------------
Default compilation has no dependencies and will compile entire set, ie:
cmake  -S . -B cmake-build

To compile methods and guest only code
--------------------------------------
This mode requires riscv toolchain to be installed in the path.
cmake -S . -B cmake-build -DCMAKE_TOOLCHAIN_FILE=cmake/riscv.cmake


Generators
----------
Tested and supported are the make and Ninja generators.

General settings
----------------
  ENABLE_TESTS         - will install Gtest and compile tests

Formatting
----------
cmake-format -i CMakeLists.txt  
https://github.com/cheshirekow/cmake_format

Testing
-------
make test
make test-<testname>

Docker Linux Build
------------------
A sample docker file that executes an entire build process under linux is provided in the cmake folder.
cd cmake
docker build . -t risc0_test
docker run risc0_test
