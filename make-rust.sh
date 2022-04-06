bazelisk build //risc0/zkvm/circuit:step_inc_gen
gcc -I ./bazel-bin -E ./rust-gen/rust-taps.h | grep -v '#' | rustfmt > risc0_taps.rs
gcc -I ./bazel-bin -E ./rust-gen/rust-poly-ops.h | grep -v '#' | rustfmt > risc0_poly_ops.rs

