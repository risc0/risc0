// Copyright 2022 Risc0, Inc.
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

#include "benchmark/benchmark.h"
#include "risc0/zkvm/sdk/cpp/host/receipt.h"

using namespace risc0;

static void BM_Simple(benchmark::State& state) {
  uint32_t num_iter = state.max_iterations;

  Prover prover("risc0/zkvm/prove/bench/bench_simple_loop");
  prover.writeInput(num_iter);

  // Google benchmark really wants to manage the benchmarking loop
  // itself, which makes it difficult to run the loop inside the
  // guest.  Work around this by only running the prover on the first
  // time through.
  if (state.KeepRunning()) {
    prover.run();

    while (state.KeepRunning()) {
    }
  }
}

BENCHMARK(BM_Simple)                //
    ->Unit(benchmark::kMicrosecond) // Display output in microseconds per run
    ->MinTime(10.0 /* seconds */)   // Run for at least 10 seconds to amortize setup overhead
    ;

BENCHMARK_MAIN();
