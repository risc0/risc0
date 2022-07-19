# Generic macros to generate custom build artifacts and copy cross compiled methods

macro(risc0_make_id name src_file)
  message("Processing risc0_make_id:" ${name} ${src_file})
  add_custom_command(
    OUTPUT ${src_file}.id
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/make-id ${src_file} ${src_file}.id
    VERBATIM
    DEPENDS ${src_file})
  add_custom_target(${name} ALL DEPENDS ${src_file}.id)
  add_dependencies(${name} make-id)
endmacro(risc0_make_id)

macro(risc0_make_circuit name output_file)
  message("Processing risc0_make_circuit:" ${name})
  add_custom_command(
    OUTPUT ${output_file}
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/make-circuit ${output_file}
    VERBATIM)
  add_custom_target(${name} ALL DEPENDS ${output_file})
  add_dependencies(${name} make-circuit)
endmacro(risc0_make_circuit)

macro(risc0_fetch_cross_artifact name input_file output_file)
  message("Processing risc0_fetch_cross_artifact:" ${name})
  add_custom_command(
    OUTPUT ${output_file}
    COMMAND ${CMAKE_COMMAND} -E copy ${input_file} ${output_file}
    VERBATIM
    DEPENDS ${input_file})
  add_custom_target(${name} ALL DEPENDS ${output_file})
  add_dependencies(${name} riscv_toolchain risc0_cross_riscv)
  add_dependencies (${name} riscv_toolchain)
endmacro(risc0_fetch_cross_artifact)
