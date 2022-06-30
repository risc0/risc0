CMake build process.
--------------------

CMake is used to build tools test and risc ELF from the VM.
CMake will install riscv toolchain as part of build process.
It is also possible to configure a tree only for the risc code or only for VM

To compile methods guest only:
cmake -G Ninja -S . -B cmake-build -DCMAKE_TOOLCHAIN_FILE=cmake/riscv.cmake

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
