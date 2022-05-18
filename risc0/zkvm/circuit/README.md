# risc0_zkvm_circuit_sys

This crate/directory contains C++ code the implements the RISC-V arithmetic circuit.

The circuit is decribed using a C++ EDSL, which leans heavily on operator
overloading.  This EDSL code then produces a primitive IR, which is 'optimized'
further, and results in the generation of code which both generates execution
traces and also evaluates the core constraint polynomials.

The rust crate exports a single function which writes this circuit out to a C++
header file.

