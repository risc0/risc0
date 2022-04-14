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

struct BenchmarkStreamWriter {
  void write_word(uint32_t word) { tot_written += sizeof(uint32_t); }
  void write_dword(uint64_t dword) { tot_written += sizeof(uint64_t); }
  void write_buffer(const void* buf, size_t len) { tot_written += align(len); }

  size_t tot_written = 0;
};
static_assert(is_stream_writer<BenchmarkStreamWriter>());

static void BM_Simple_Loop(benchmark::State& state) {
  uint32_t num_iter = state.range(0);
  size_t tot_iter = 0;

  for (auto _ : state) {
    Prover prover("risc0/zkvm/prove/bench/bench_simple_loop");
    prover.writeInput(num_iter);
    VectorStreamWriter receipt_buf;
    Receipt receipt = prover.run();
    BenchmarkStreamWriter writer;
    ArchiveWriter<BenchmarkStreamWriter> archive(writer);
    archive.transfer(receipt);

    tot_iter += num_iter;
    state.counters["receipt_size"] = writer.tot_written;
  }

  state.SetItemsProcessed(tot_iter);
}

BENCHMARK(BM_Simple_Loop)           //
    ->Unit(benchmark::kMillisecond) // Display output in milliseconds per run
    ->Arg(1) // Number of iterations in guest
    ->Arg(10)
    ->Arg(100)
    ->DenseRange(1000, 50000, 1000)
    ;

BENCHMARK_MAIN();
