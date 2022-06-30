CMake build process.
--------------------

CMake is used to build a full set of c++ code.
CMake will install riscv toolchain as part of build process, if run by default.
It is also possible to configure a tree only for the riscv code.

Full compilation
-----------------
Default compilation has no dependencies and will compile entire set, ie:
cmake  -S . -B cmake-build

To compile methods guest only
-------------------------------
This mode requires riscv toolchain to be installed in the path.
cmake -S . -B cmake-build -DCMAKE_TOOLCHAIN_FILE=cmake/riscv.cmake


Generators
---------------
Tested and supported are the make and Ninja generators.

General settings
----------------
  ENABLE_TESTS         - will install Gtest and compile tests
  BUILD_RISCVM         - will build native set
  BUILD_CROSS_RISC     - will also compile methods via cross
  BUILD_EMBEDDED_RISC  - will compile methods as a part of the single tree

Linux Docker
----------------
A sample docker file that executes an entire build process under linux is provided in the cmake folder.

Formatting
---------------
cmake-format -i CMakeLists.txt  
https://github.com/cheshirekow/cmake_format

Testing
---------------
make test
make test-<testname>

Docker Linux Build
---------------
cd cmake
docker build . -t risc0_test
docker run risc0_test
