add_library(zkvm-verify
	method_id.cpp 
	riscv.cpp
)

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/risc0/zkvm/circuit/step.cpp.inc COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/make-circuit ${CMAKE_BINARY_DIR}/risc0/zkvm/circuit/step.cpp.inc  VERBATIM) 

add_custom_target(step.inc ALL DEPENDS ${CMAKE_BINARY_DIR}/risc0/zkvm/circuit/step.cpp.inc)
add_dependencies(step.inc make-circuit)
add_dependencies(zkvm-verify step.inc)


