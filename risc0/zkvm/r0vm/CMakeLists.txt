add_executable(r0vm r0vm.cpp)
target_link_libraries(r0vm zkvm-circuit zkvm-sdk-cpp-host zkvm-prove zkvm-verify zkp-verify zkp-accel-backend-cpu zkp-prove zkp-core core)
