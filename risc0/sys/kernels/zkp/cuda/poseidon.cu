// Copyright 2023 Risc0, Inc.
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

#include "fp.h"

#define CELLS 24
#define ROUNDS_FULL 8
#define ROUNDS_HALF_FULL (ROUNDS_FULL / 2)
#define ROUNDS_PARTIAL 21
#define ROW_SIZE (CELLS + ROUNDS_PARTIAL)
#define CELLS_RATE 16
#define CELLS_OUT 8

namespace poseidon {

__device__ void add_round_constants(const Fp* ROUND_CONSTANTS, Fp* cells, uint round) {
  for (uint i = 0; i < CELLS; i++) {
    cells[i] += ROUND_CONSTANTS[round * CELLS + i];
  }
}

__device__ Fp sbox(Fp x) {
  Fp x2 = x * x;
  Fp x4 = x2 * x2;
  Fp x6 = x4 * x2;
  return x6 * x;
}

__device__ void do_full_sboxes(Fp* cells) {
  for (uint i = 0; i < CELLS; i++) {
    cells[i] = sbox(cells[i]);
  }
}

__device__ void multiply_by_mds(const Fp* MDS, Fp* cells) {
  Fp new_cells[CELLS];
  for (uint i = 0; i < CELLS; i++) {
    Fp tot = 0;
    for (uint j = 0; j < CELLS; j++) {
      tot += MDS[i * CELLS + j] * cells[j];
    }
    new_cells[i] = tot;
  }
  for (uint i = 0; i < CELLS; i++) {
    cells[i] = new_cells[i];
  }
}

__device__ void full_round(const Fp* ROUND_CONSTANTS, const Fp* MDS, Fp* cells, uint round) {
  add_round_constants(ROUND_CONSTANTS, cells, round);
  do_full_sboxes(cells);
  multiply_by_mds(MDS, cells);
}

__device__ void poseidon_mix(const Fp* ROUND_CONSTANTS,
                             const Fp* MDS,
                             const Fp* PARTIAL_COMP_MATRIX,
                             const Fp* PARTIAL_COMP_OFFSET,
                             Fp* cells) {
  uint round = 0;
  for (uint i = 0; i < ROUNDS_HALF_FULL; i++) {
    full_round(ROUND_CONSTANTS, MDS, cells, round);
    round++;
  }
  Fp sboxes[ROUNDS_PARTIAL];
  for (uint i = 0; i < ROUNDS_PARTIAL; i++) {
    // For each sbox, compute it's input
    Fp sbox_in = PARTIAL_COMP_OFFSET[CELLS + i];
    for (uint j = 0; j < CELLS; j++) {
      sbox_in += PARTIAL_COMP_MATRIX[(CELLS + i) * ROW_SIZE + j] * cells[j];
    }
    for (uint j = 0; j < i; j++) {
      sbox_in += PARTIAL_COMP_MATRIX[(CELLS + i) * ROW_SIZE + CELLS + j] * sboxes[j];
    }
    // Run it through the sbox + record it
    sboxes[i] = sbox(sbox_in);
  }
  // Forward output data back to cells
  Fp new_cells[CELLS];
  for (uint i = 0; i < CELLS; i++) {
    Fp out = PARTIAL_COMP_OFFSET[i];
    for (uint j = 0; j < CELLS; j++) {
      out += PARTIAL_COMP_MATRIX[i * ROW_SIZE + j] * cells[j];
    }
    for (uint j = 0; j < ROUNDS_PARTIAL; j++) {
      out += PARTIAL_COMP_MATRIX[i * ROW_SIZE + CELLS + j] * sboxes[j];
    }
    new_cells[i] = out;
  }
  round += ROUNDS_PARTIAL;
  for (uint i = 0; i < CELLS; i++) {
    cells[i] = new_cells[i];
  }
  for (uint i = 0; i < ROUNDS_HALF_FULL; i++) {
    full_round(ROUND_CONSTANTS, MDS, cells, round);
    round++;
  }
}

} // namespace poseidon

__global__ void poseidon_fold(const Fp* ROUND_CONSTANTS,
                              const Fp* MDS,
                              const Fp* PARTIAL_COMP_MATRIX,
                              const Fp* PARTIAL_COMP_OFFSET,
                              Fp* output,
                              const Fp* input,
                              uint32_t output_size) {
  uint32_t gid = blockDim.x * blockIdx.x + threadIdx.x;
  if (gid >= output_size) {
    return;
  }
  Fp cells[CELLS];
  for (size_t i = 0; i < CELLS_OUT; i++) {
    cells[i] = input[2 * gid * CELLS_OUT + i];
    cells[CELLS_OUT + i] = input[(2 * gid + 1) * CELLS_OUT + i];
  }
  poseidon::poseidon_mix(ROUND_CONSTANTS, MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, cells);
  for (uint i = 0; i < CELLS_OUT; i++) {
    output[gid * CELLS_OUT + i] = cells[i];
  }
}

__global__ void poseidon_rows(const Fp* ROUND_CONSTANTS,
                              const Fp* MDS,
                              const Fp* PARTIAL_COMP_MATRIX,
                              const Fp* PARTIAL_COMP_OFFSET,
                              Fp* out,
                              const Fp* matrix,
                              uint32_t count,
                              uint32_t col_size) {
  uint32_t gid = blockDim.x * blockIdx.x + threadIdx.x;
  if (gid >= count) {
    return;
  }
  Fp cells[CELLS];
  uint used = 0;
  for (uint i = 0; i < col_size; i++) {
    cells[used++] += matrix[i * count + gid];
    if (used == CELLS_RATE) {
      poseidon::poseidon_mix(ROUND_CONSTANTS, MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, cells);
      used = 0;
    }
  }
  if (used != 0 || count == 0) {
    poseidon::poseidon_mix(ROUND_CONSTANTS, MDS, PARTIAL_COMP_MATRIX, PARTIAL_COMP_OFFSET, cells);
  }
  for (uint i = 0; i < CELLS_OUT; i++) {
    out[CELLS_OUT * gid + i] = cells[i];
  }
}
