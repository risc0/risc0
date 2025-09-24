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

#include "rv32im/emu/poseidon2.h"

using risc0::p2impl::cells_t;
using risc0::p2impl::poseidonMultiplyByMExt;
using risc0::p2impl::poseidonDoExtRound;
using risc0::p2impl::poseidonDoIntRounds;

namespace risc0::rv32im {

void toFpDigest(FpDigest& out, const Digest& in) {
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    out[i] = Fp::fromRaw(in.words[i]);
  }
}

Poseidon2Witgen::Poseidon2Witgen(Trace& trace) : trace(trace) {}

Digest Poseidon2Witgen::doBlock(Digest in, const std::array<Fp, CELLS_RATE>& data, bool isFinal) {
  // Create full cells
  cells_t cells;
  for (size_t i = 0; i < CELLS_RATE; i++) {
    cells[i] = data[i];
  }
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    cells[CELLS_RATE + i] = Fp::fromRaw(in.words[i]);
  }
  // Check if we already have a witness for this one
  auto it = saved.find(cells);
  if (it != saved.end()) {
    auto* block = it->second;
    Digest out;
    for (size_t i = 0; i < CELLS_DIGEST; i++) {
      out.words[i] = (isFinal ? block->out[i] : block->out[CELLS_RATE + i]).asRaw();
    }
    if (isFinal) {
      block->outUseCount++;
    } else {
      block->contUseCount++;
    }
    return out;
  }
  // Otherwise build the witness data for the full block it's parts
  // TODO: we can move the details to another thread
  auto* block = &trace.makeP2Block();
  block->outUseCount = 0;
  block->contUseCount = 0;
  saved[cells] = block;
  uint32_t id = trace.getGlobals().p2Count++;
  block->id = id;
  if (isFinal) {
    block->outUseCount++;
  } else {
    block->contUseCount++;
  }
  for (size_t i = 0; i < CELLS; i++) {
    block->in[i] = cells[i];
  }
  poseidonMultiplyByMExt(cells);
  for (size_t i = 0; i < ROUNDS_HALF_FULL; i++) {
    auto& extRound = trace.makeP2ExtRound();
    extRound.id = id;
    extRound.round = i;
    for (size_t j = 0; j < CELLS; j++) {
      extRound.cells[j] = cells[j];
    }
    poseidonDoExtRound(cells, i);
  }
  auto& intRound = trace.makeP2IntRounds();
  for (size_t i = 0; i < CELLS; i++) {
    intRound.id = id;
    intRound.cells[i] = cells[i];
  }
  poseidonDoIntRounds(cells);
  for (size_t i = 0; i < ROUNDS_HALF_FULL; i++) {
    auto& extRound = trace.makeP2ExtRound();
    extRound.id = id;
    extRound.round = ROUNDS_HALF_FULL + i;
    for (size_t j = 0; j < CELLS; j++) {
      extRound.cells[j] = cells[j];
    }
    poseidonDoExtRound(cells, ROUNDS_HALF_FULL + i);
  }
  for (size_t i = 0; i < CELLS; i++) {
    block->out[i] = cells[i];
  }
  Digest out;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    out.words[i] = (isFinal ? cells[i] : cells[CELLS_RATE + i]).asRaw();
  }
  return out;
}

}  // namespace risc0::rv32im
