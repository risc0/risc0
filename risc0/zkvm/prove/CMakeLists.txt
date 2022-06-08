add_library(zkvm-prove
	exec.cpp		
	io_handler.cpp		
	method_id.cpp		
	riscv.cpp		
	step.cpp		
	step_context.cpp
)
target_link_libraries(zkvm-prove  TBB::tbb)
add_dependencies(zkvm-prove step.inc )

add_subdirectory(make-id)
add_subdirectory(test)
