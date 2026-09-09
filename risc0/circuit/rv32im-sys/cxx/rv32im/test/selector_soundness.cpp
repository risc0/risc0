// Copyright 2026 RISC Zero, Inc.
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
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "prove/prove.h"
#include "prove/rv32im.h"

using risc0::RowInfo;

#include "rv32im/circuit/data_witgen.h"
#include "rv32im/witness/ecall.h"
#include "verify/rv32im.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using namespace risc0;

namespace {

constexpr size_t kPo2 = 12;
constexpr size_t kRows = size_t(1) << kPo2;
constexpr uint32_t kForgedOutput = 0xdeadbeef;

uint32_t readU32(OutU32 val) {
  return val.low.asUInt32() | (val.high.asUInt32() << 16);
}

void forgeOutput(PreflightResults& preflight) {
  for (const RowInfo& row : preflight.rowInfo) {
    if (row.rowType == uint8_t(BlockType::EcallTerminate)) {
      auto* witness =
          reinterpret_cast<EcallTerminateWitness*>(preflight.aux.data() + row.auxOffset);
      if (witness->output[0].value != 0) {
        throw std::runtime_error("Unexpected initial journal value");
      }
      witness->output[0].value = kForgedOutput;
      return;
    }
  }
  throw std::runtime_error("Missing EcallTerminate witness");
}

// Construct the malicious witness used to reproduce the soundness issue. The forged memory read
// leaves an unmatched lookup argument. Resetting the running lookup sum on a row whose selector
// has no accumulator constraints hides that mismatch from the vulnerable verifier.
void expectForgeryRejected(uint32_t unconstrainedSelector) {
  IHalPtr hal = getCpuHal();
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernelV2(words, "rv32im/test/seal_test_kernel");
  auto image = rv32im::MemoryImage::fromWords(words);
  rv32im::NullHostIO io;
  auto preflight = risc0::preflight(kPo2, image, io);
  if (!preflight->isFinal || preflight->rowInfo.size() != kRows ||
      preflight->rowInfo.back().rowType != uint8_t(BlockType::Empty)) {
    throw std::runtime_error("Unexpected preflight layout");
  }
  forgeOutput(*preflight);

  auto rowInfo = hal->allocateArray<RowInfo>(kRows);
  auto aux = hal->allocateArray<uint32_t>(kRows * rv32im::computeMaxWitPerRow());
  auto tables = hal->allocateArray<uint32_t>(256 + 65536 + 20 * kRows);
  rowInfo.copyFromCpu(hal, preflight->rowInfo.data(), preflight->rowInfo.size());
  aux.copyFromCpu(hal, preflight->aux.data(), preflight->aux.size());

  Rv32CircuitInfo circuit(hal, rowInfo, aux, tables, false);
  auto honestDataWitgen = circuit.ci.groups[0].witgen;
  circuit.ci.groups[0].witgen =
      [hal, honestDataWitgen, unconstrainedSelector](std::vector<GroupState>& state) {
        honestDataWitgen(state);
        PinnedMatrixRW<Fp> data(hal, state[0].table);
        using Context = DataWitgenContext<kPo2>;
        Context ctx{};
        auto* top = reinterpret_cast<Top<Context>*>(data.data() + kRows - 1);
        top->select.set(ctx, unconstrainedSelector);
      };

  auto honestAccumWitgen = circuit.ci.groups[1].witgen;
  circuit.ci.groups[1].witgen = [hal, honestAccumWitgen](std::vector<GroupState>& state) {
    honestAccumWitgen(state);
    PinnedMatrixRW<Fp> accum(hal, state[1].table);
    for (size_t i = 0; i < 4; i++) {
      accum(kRows - 1, i) = 0;
    }
  };

  Prover prover(hal, circuit.ci, kPo2);
  WriteIop wiop;
  prover.prove(wiop);

  const std::vector<Fp>& transcript = wiop.getTranscript();
  const Globals* globals = reinterpret_cast<const Globals*>(transcript.data());
  if (readU32(globals->out[0]) != kForgedOutput) {
    throw std::runtime_error("Failed to construct forged journal");
  }

  ReadIop riop(transcript.data(), transcript.size());
  try {
    verifyRv32im(riop, kPo2);
  } catch (const std::runtime_error& err) {
    if (std::string(err.what()) == "Poly check failed") {
      return;
    }
    throw;
  }
  throw std::runtime_error("Verifier accepted a forged journal");
}

} // namespace

int main() {
  static_assert(NUM_BLOCK_TYPES < MAJOR_SPLIT_SIZE * MINOR_SPLIT_SIZE);

  // Empty was omitted from the block-specific accumulator constraints.
  expectForgeryRejected(uint32_t(BlockType::Empty));

  // TwoHot admits four encodings beyond the declared BlockType range.
  expectForgeryRejected(NUM_BLOCK_TYPES);
  return 0;
}
