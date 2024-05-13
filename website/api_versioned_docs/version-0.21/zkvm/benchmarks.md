# Performance Benchmarks

## Pregenerated benchmarks

We have [a performance datasheet][datasheet] with runtime and memory performance
information. This information is organized by both program size and hardware
target, and includes both CPU and GPU targets. The datasheet also includes the
RISC Zero zkVM version used and the size of several example programs to give
context for the [cycle count] size data.

## Generating your own benchmarks

You can generate benchmarks yourself to get performance data for your exact
system, or if you want benchmarks for a different RISC Zero zkVM version than
used in the datasheet.

To generate benchmarks, first [install Rust and the RISC Zero
toolchain][install] and clone the [risc0 repository] if you haven't already done
so. Navigate to the risc0 source code directory and, if necessary, check out the
branch or tag you wish to generate benchmarks for. Then run:

```bash
cargo run --release --example loop
```

This will produce the benchmark data shown in the [datasheet] for your system
(using the CPU) on the checked out version of the RISC Zero zkVM.

If you want to benchmark a GPU, you will need to build with the `cuda` or
`metal` feature enabled (whichever is appropriate for your hardware). To do
this, use the following commands:

- **Metal**

```bash
cargo run --release -F metal --example loop
```

- **CUDA**

```bash
cargo run --release -F cuda --example loop
```

We also have a Fibonacci computation benchmark, which you can run with

```bash
cargo bench --bench fib
```

This will compute the 100th, 1000th, and 10000th Fibonacci numbers modulo 2^64
(ten times for each). It will report both time and throughput (how many numbers
were added per second) with separate statistics for [execution] and
[proving][prover]. As with the loop benchmark, the Fibonacci benchmark will use
the CPU by default, and you can benchmark a CUDA or Metal GPU by setting the
appropriate feature flag.

[cycle count]: /terminology#clock-cycles
[datasheet]: https://benchmarks.risczero.com/release-0.21/datasheet
[execution]: /terminology#execute
[install]: ./install.md
[prover]: /terminology#prover
[risc0 repository]: https://github.com/risc0/risc0
