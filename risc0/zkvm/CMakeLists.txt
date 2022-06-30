add_subdirectory(sdk)

if(NOT BUILD_RISCVCROSS)
  add_subdirectory(verify)
  add_subdirectory(circuit)
endif()

  
add_subdirectory(prove)
