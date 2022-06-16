add_library(zkvm-verify
  riscv.cpp
)

risc0_make_circuit(step.inc ${CMAKE_BINARY_DIR}/risc0/zkvm/circuit/step.cpp.inc)
add_dependencies(zkvm-verify step.inc )
