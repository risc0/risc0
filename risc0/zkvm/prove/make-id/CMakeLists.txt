add_executable(make-id make-id.cpp)
target_link_libraries(make-id
  zkvm-circuit
  zkvm-prove
  zkvm-verify
  zkp-prove
  zkp-verify
  zkp-accel-backend-cpu
  zkp-prove
  zkp-core
  core
  TBB::tbb
)
