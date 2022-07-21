bazelisk build //risc0/zkvm/circuit:step_inc_gen
gcc -I ./bazel-bin -E ./rust-gen/risc0_taps.rs.h | grep -v '#' | rustfmt > risc0_taps.rs
gcc -I ./bazel-bin -E ./rust-gen/risc0_poly_ops.rs.h | grep -v '#' | rustfmt > risc0_poly_ops.rs

