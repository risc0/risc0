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

static void BM_Simple_Loop(benchmark::State& state) {
  uint32_t num_iter = state.range(0);
  size_t tot_iter = 0;

  for (auto _ : state) {
    Prover prover("risc0/zkvm/prove/bench/bench_simple_loop");
    prover.writeInput(num_iter);
    prover.run();

    tot_iter += num_iter;
  }

  state.SetItemsProcessed(tot_iter);
}

BENCHMARK(BM_Simple_Loop)           //
    ->Unit(benchmark::kMillisecond) // Display output in milliseconds per run
    ->Range(1, 65536)               // Iterations per loop in guest
    ;

BENCHMARK_MAIN();
