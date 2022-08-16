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

#include "risc0/core/rng.h"
#include "risc0/zkp/core/ntt.h"

using namespace risc0;

static void BM_Interpolate_NTT(benchmark::State& state) {
  size_t n = state.range(0);
  size_t size = 1 << n;

  std::vector<Fp> buf(size);
  PseudoRng rng(2);
  for (size_t i = 0; i < size; i++) {
    buf[i] = Fp::random(rng);
  }

  for (auto _ : state) {
    interpolateNTT(buf.data(), size);
  }
}

BENCHMARK(BM_Interpolate_NTT)->Unit(benchmark::kMillisecond)->Arg(10)->Arg(15)->Arg(20);

BENCHMARK_MAIN();
