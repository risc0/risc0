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

#include <gtest/gtest.h>

#include <random>

#include "hal/dual/dual.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"

using namespace risc0;

void testProve(IHalPtr hal) {
  size_t po2 = 12;
  Rv32imProver prover(hal, po2);
  LOG(0, "Loading elf");
  auto image = rv32im::MemoryImage::fromRawElf("rv32im/test/benchmark_kernel");
  LOG(0, "Running first segment");
  rv32im::NullHostIO io;
  prover.preflight(image, io);
  WriteIop writeIop;
  LOG(0, "Proving");
  prover.prove(writeIop);
  std::vector<Fp> transcript = writeIop.getTranscript();
  LOG(0, "Transcipt size = " << transcript.size());
  LOG(0, "Verifying");
  ReadIop readIop(transcript.data(), transcript.size());
  verifyRv32im(readIop, po2);
  readIop.done();
}

TEST(prove, cpu) {
  testProve(getCpuHal());
}

TEST(prove, gpu) {
  testProve(getGpuHal());
}

/*
TEST(prove, dual) {
  IHalPtr cpu = getCpuHal();
  IHalPtr gpu = getGpuHal();
  IHalPtr dual = getDualHal(cpu, gpu);
  testProve(dual);
}
*/
