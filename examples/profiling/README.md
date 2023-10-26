# Profiling guest code

In this example we demonstrate how to profile different implementations of the Fibonacci sequence calculation on the RISC0 ZKVM.

## Overview

There are three different Fibonacci sequence calculation methods provided:

1. `fibonacci_1`: A basic iterative method.
2. `fibonacci_2`: An optimized iterative method that attempts to batch computation.
3. `fibonacci_3`: A matrix exponentiation approach, which is a fast method to compute Fibonacci numbers.

The host code sets up a profiling environment and then runs the RISC0 guest code that computes Fibonacci numbers using the three methods. After execution, the profiling data is written out for further analysis.

The guest code reads the number of iterations from the host, computes the Fibonacci number, and finally commits the answer back to the host.

## Usage

### Step 1: Prerequisites
First, [install Rust] if you don't already have it.

Next, install the `cargo-risczero` tool and install the toolchain with:
```bash
cargo install cargo-binstall
cargo binstall cargo-risczero
cargo risczero install
```

Finally, install the [pprof] tool with
```bash
go install github.com/google/pprof@latest
```

### Step 2: Running
Then, run the example with:
```bash
RISC0_PPROF_OUT=./profile.pb cargo run --release
```

The above command will run the Fibonacci computation for 1000 iterations and write the profiling output to profile.pb.

### Step 3: Visualization
To visualize the profiling data using `pprof`, run:
```bash
pprof -http=127.0.0.1:8089 ../target/riscv-guest/riscv32im-risc0-zkvm-elf/release/fibonacci profile.pb
```

Then navigate to http://localhost:8089 in your browser.

## What to Expect
When you visualize the profiling data, you should be able to see the relative performance of the three Fibonacci implementations. This can be helpful in understanding the efficiency of various algorithms and their performance implications.

## Notes
- Ensure that the environment variable `RISC0_PPROF_OUT` is set to the desired output path for the profiling data.
- The Fibonacci functions are annotated with `#[inline(never)]` and `#[no_mangle]` to ensure that their symbols are easily recognizable in the profiling data.
- The `black_box` function is used to prevent the compiler from optimizing out the calculations.

[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[pprof]: https://github.com/google/pprof
