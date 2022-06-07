add_executable(make-id make-id.cpp)
target_link_libraries(make-id core zkvm-prove zkvm-verify zkvm-circuit zkp-prove  zkp-verify zkp-core zkp-accel-backend-cpu TBB::tbb)
