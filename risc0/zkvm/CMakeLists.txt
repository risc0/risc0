add_subdirectory(sdk)

if(NOT BUILD_RISCVCROSS)
  add_subdirectory(verify)
  add_subdirectory(circuit)
endif()

  
add_subdirectory(prove)

if(BUILD_RISCVM)
  add_subdirectory(r0vm)
endif()
