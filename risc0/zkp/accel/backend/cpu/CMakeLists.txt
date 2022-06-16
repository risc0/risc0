add_library(zkp-accel-backend-cpu
  impl.cpp
)

target_link_libraries(zkp-accel-backend-cpu
  TBB::tbb
)
