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

std::string writeReceipts;

size_t save_receipt(Prover& prover, std::string receipt_file) {
  VectorStreamWriter receipt_buf;
  Receipt receipt = prover.run();
  VectorStreamWriter writer;
  ArchiveWriter<VectorStreamWriter> archive(writer);
  archive.transfer(receipt);

  if (!writeReceipts.empty()) {
    FILE* f = fopen((writeReceipts + "/" + receipt_file).c_str(), "w");
    if (!f) {
      perror(receipt_file.c_str());
      exit(1);
    }

    size_t nwrote = fwrite(writer.vec.data(), sizeof(uint32_t), writer.vec.size(), f);
    if (nwrote != writer.vec.size()) {
      fprintf(stderr, "Short write writing receipt\n");
      exit(1);
    }
    fclose(f);
  }
  return writer.vec.size() * sizeof(uint32_t);
}

static void BM_Simple_Loop(benchmark::State& state) {
  uint32_t num_iter = state.range(0);
  size_t tot_iter = 0;

  for (auto _ : state) {
    Prover prover("risc0/zkvm/prove/bench/bench_simple_loop");
    prover.writeInput(num_iter);

    state.counters["receipt_size"] =
        save_receipt(prover, "bench_simple_loop_" + std::to_string(num_iter) + ".receipt");
    tot_iter += num_iter;
  }

  state.SetItemsProcessed(tot_iter);
}

static void BM_Sha(benchmark::State& state) {
  uint32_t num_iter = state.range(0);
  size_t tot_iter = 0;

  for (auto _ : state) {
    Prover prover("risc0/zkvm/prove/bench/bench_sha");
    prover.writeInput(num_iter);

    state.counters["receipt_size"] =
        save_receipt(prover, "bench_sha_" + std::to_string(num_iter) + ".receipt");
    tot_iter += num_iter;
  }

  state.SetItemsProcessed(tot_iter);
}

BENCHMARK(BM_Simple_Loop)           //
    ->Unit(benchmark::kMillisecond) // Display output in milliseconds per run
    ->Arg(1)                        // Number of iterations in guest
    ->Arg(10)
    ->Arg(100)
    ->DenseRange(1000, 10000, 1000);

BENCHMARK(BM_Sha)->Unit(benchmark::kMillisecond)->Arg(1)->Arg(10)->Arg(100);

// Helper macro to create a main routine in a test that runs the benchmarks
int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  if (argc >= 3 && !strcmp(argv[1], "--write-receipts")) {
    writeReceipts = argv[2];
    argc -= 2;
    argv += 2;
  }
  if (::benchmark::ReportUnrecognizedArguments(argc, argv))
    return 1;
  ::benchmark::RunSpecifiedBenchmarks();
  ::benchmark::Shutdown();
  return 0;
}
