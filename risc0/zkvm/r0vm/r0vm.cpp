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

#include <stdio.h>

#include "risc0/zkvm/sdk/cpp/host/receipt.h"

using namespace risc0;

constexpr size_t kMaxStdin = 64 * 1024;

int main(int argc, char* argv[]) {
  // Check args
  if (argc != 2) {
    fprintf(stderr, "Usage: r0vm <elf_path>\n");
    return 1;
  }
  // Consume stdin fully
  std::vector<char> data(kMaxStdin);
  size_t count = fread(data.data(), 1, kMaxStdin, stdin);
  if (count >= kMaxStdin) {
    fprintf(stderr, "Input too large\n");
    return 1;
  }
  if (!feof(stdin)) {
    fprintf(stderr, "Error reading from stdin\n");
    return 1;
  }
  try {
    MethodId methodId = computeMethodId(argv[1]);
    Prover prover(argv[1], methodId);
    prover.writeInput(data.data(), count);
    // Run prover
    Receipt receipt = prover.run();
    // Write private output
    const BufferU8& out = prover.getOutput();
    size_t stdoutSize = fwrite(out.data(), 1, out.size(), stdout);
    if (stdoutSize != out.size()) {
      fprintf(stderr, "Failed on writing to stdout");
      return 1;
    }
    // Serialize receipt
    VectorStreamWriter writer;
    ArchiveWriter<VectorStreamWriter> archive(writer);
    archive.transfer(receipt);
    // Write receipt to stderr
    size_t stderrSize = fwrite(writer.vec.data(), 4, writer.vec.size(), stderr);
    if (stderrSize != writer.vec.size()) {
      return 1;
    }
  } catch (const std::exception& e) {
    fprintf(stderr, "Error running proof: %s\n", e.what());
    return 1;
  }
  return 0;
}
