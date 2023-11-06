# Guest Profiling Guide

In this guide, we'll explore how to effectively profile guest code within the RISC Zero zkVM, offering insights and tools to improve performance.
We'll be using three different implementations of the Fibonacci sequence calculation to demonstrate how to profile guest code.
You can find all the code used as example in the [profiling example].

## Background

Profiling tools, like [pprof] and [perf], allow collecting performance information over the entire execution of your program, and help create visualizations for the performance of your program.
RISC Zero has experimental support for generating pprof files for cycle counts.

[Sampling CPU profilers], as implemented by pprof and perf, provide a view of where your program is spending its time.
It does so by recording the current call stack at a sampling interval.
RISC Zero provides a "sampling" [^1] CPU profiler for guest execution.

[pprof]: https://github.com/google/pprof
[perf]: https://perf.wiki.kernel.org/index.php/Main_Page
[Sampling CPU profilers]: https://nikhilism.com/post/2018/sampling-profiler-internals-introduction/

## Overview

### Guest code

There are three different Fibonacci sequence calculation methods provided in the [profiling example]:

1. `fibonacci_1`: A basic iterative method.
2. `fibonacci_2`: An optimized iterative method that attempts to batch computation.
3. `fibonacci_3`: A matrix exponentiation approach, which is a fast method to compute Fibonacci numbers.

The guest code reads the number of iterations from the host, computes the Fibonacci number using all the above methods, and finally commits the answer back to the host.

### Host code

Here's are the step to enable profiling:

1. Enable the `profile` feature of the `zkvm` in your `Cargo.toml`.

```toml
risc0-zkvm = { version = "0.18", features = ["profiler"] }
```

2. Initialize the profiler with your guest code.

```rust
# use fibonacci_methods::{FIBONACCI_ELF, FIBONACCI_PATH};
# use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};
let mut profiler = Profiler::new("profile_output_path", FIBONACCI_ELF);
```

This will initialize the profiler using the `FIBONACCI_ELF` as guest code, and will write the output of the profiling to `profile_output_path`.
Alternatively, you can define the `profile_output_path` using an env variable:

```rust
# use fibonacci_methods::{FIBONACCI_ELF, FIBONACCI_PATH};
# use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};
let pprof_out = match std::env::var("RISC0_PPROF_OUT") {
    Ok(val) => Some(val),
    Err(_) => None,
};
let mut profiler = match pprof_out {
    Some(path) => Some(Profiler::new(&path, FIBONACCI_ELF).expect("profiler creation failed")),
    None => None,
};
```

3. Build the executor environment

```rust
# use fibonacci_methods::{FIBONACCI_ELF, FIBONACCI_PATH};
# use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};
# let pprof_out = match std::env::var("RISC0_PPROF_OUT") {
#     Ok(val) => Some(val),
#     Err(_) => None,
# };
# let mut profiler = match pprof_out {
#     Some(path) => Some(Profiler::new(&path, FIBONACCI_ELF).expect("profiler creation failed")),
#     None => None,
# };
let iterations = 1000;
let env = {
    let mut builder = ExecutorEnv::builder();
    if let Some(ref mut p) = profiler {
        builder.trace_callback(p.make_trace_callback());
    }
    builder
        .write_slice(&[iterations])
        .build()
        .expect("environment build failed")
};
```

4. Execute the guest code

```rust
# use fibonacci_methods::{FIBONACCI_ELF, FIBONACCI_PATH};
# use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};
# let pprof_out = match std::env::var("RISC0_PPROF_OUT") {
#     Ok(val) => Some(val),
#     Err(_) => None,
# };
# let mut profiler = match pprof_out {
#     Some(path) => Some(Profiler::new(&path, FIBONACCI_ELF).expect("profiler creation failed")),
#     None => None,
# };
# let iterations = 1000;
# let env = {
#     let mut builder = ExecutorEnv::builder();
#     if let Some(ref mut p) = profiler {
#         builder.trace_callback(p.make_trace_callback());
#     }
#     builder
#         .write_slice(&[iterations])
#         .build()
#         .expect("environment build failed")
# };
let exec = default_executor();
exec.execute_elf(env, FIBONACCI_ELF).expect("execution failed");
```

This will only [execute] the guest code, without generating a [receipt].

5. Write out the profile

```rust
# use fibonacci_methods::{FIBONACCI_ELF, FIBONACCI_PATH};
# use risc0_zkvm::{default_executor, ExecutorEnv, Profiler};
# let pprof_out = match std::env::var("RISC0_PPROF_OUT") {
#     Ok(val) => Some(val),
#     Err(_) => None,
# };
# let mut profiler = match &pprof_out {
#     Some(path) => Some(Profiler::new(&path, FIBONACCI_ELF).expect("profiler creation failed")),
#     None => None,
# };
# let iterations = 1000;
# let env = {
#     let mut builder = ExecutorEnv::builder();
#     if let Some(ref mut p) = profiler {
#         builder.trace_callback(p.make_trace_callback());
#     }
#     builder
#         .write_slice(&[iterations])
#         .build()
#         .expect("environment build failed")
# };
# let exec = default_executor();
# exec.execute_elf(env, FIBONACCI_ELF).expect("execution failed");
if let Some(ref mut p) = profiler {
    p.finalize();
    let report = p.encode_to_vec();
    std::fs::write(pprof_out.as_ref().unwrap(), &report)
        .expect("Unable to write profiling output");
}
```

## Usage

### Step 1: Prerequisites

First, install the [pprof] tool with

```bash
go install github.com/google/pprof@latest
```

### Step 2: Running

Then, run the example with:

```bash
RISC0_PPROF_OUT=./profile.pb cargo run --release
```

The above command will [execute] the Fibonacci computation for 1000 iterations and write the profiling output to profile.pb.

### Step 3: Visualization

To visualize the profiling data using `pprof`, run:

```bash
pprof -http=127.0.0.1:8089 ../target/riscv-guest/riscv32im-risc0-zkvm-elf/release/fibonacci profile.pb
```

Then navigate to http://localhost:8089 in your browser.

## What to Expect

When you visualize the profiling data, you should be able to see the relative performance in terms of [cycle count] of the three Fibonacci implementations.
This can be helpful in understanding the efficiency of various algorithms and their performance implications.

![Graph](/img/profiling_graph.png)
![Flamegraph](/img/profiling_flamegraph.png)

## Notes

- Ensure that the environment variable `RISC0_PPROF_OUT` is set to the desired output path for the profiling data.
- The Fibonacci functions are annotated with `#[inline(never)]` and `#[no_mangle]` to ensure that their symbols are easily recognizable in the profiling data.
- The `black_box` function is used to prevent the compiler from optimizing out the calculations.
- To maximize the number of nodes visualized by [pprof] you can add `-edgefraction 0 -nodefraction 0 -nodecount 100000` when starting [pprof].

[profiling example]: https://github.com/risc0/risc0/examples/profiling
[receipt]: /terminology#receipt
[cycle count]: /terminology#clock-cycles
[execute]: /terminology#execute

[^1]:
    Here “sampling” is in quotes because the profiler actually captures the call stack at every cycle of program execution. Capturing a call stack on every cycle of execution is not done in most programs on physical CPUs for a few reasons:

    - It would be cost prohibitive to do so for all but quite short program executions.
    - Introducing such heavy profiling would actually alter the performance characteristics in significant ways.

    In zkVM execution, executions are generally short and all execution is synchronous and is not subject to any deviations in behavior due to measurement overhead.
