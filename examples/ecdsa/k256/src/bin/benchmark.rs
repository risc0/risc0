// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use k256_methods::BENCHMARK_ELF;
use risc0_zkvm::{ExecutorEnv, default_executor};

// Simple main to load and run the benchmark binary in the RISC Zero Executor.
fn main() {
    let env = ExecutorEnv::builder().build().unwrap();
    let exec = default_executor();
    std::hint::black_box(exec.execute(env, BENCHMARK_ELF)).unwrap();
}
