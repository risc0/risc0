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
#include "sha256.h"

#define CELLS 24
#define ROUNDS_FULL 8
#define ROUNDS_HALF_FULL (ROUNDS_FULL / 2)
#define ROUNDS_PARTIAL 21
#define ROW_SIZE (CELLS + ROUNDS_PARTIAL)
#define CELLS_RATE 16
#define CELLS_OUT 8

namespace poseidon2 {

__device__ void add_round_constants_full(const Fp* ROUND_CONSTANTS, Fp* cells, uint round) {
  for (uint i = 0; i < CELLS; i++) {
    cells[i] += ROUND_CONSTANTS[round * CELLS + i];
  }
}

__device__ void add_round_constants_partial(const Fp* ROUND_CONSTANTS, Fp* cells, uint round) {
  cells[0] += ROUND_CONSTANTS[round * CELLS];
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

__device__ void do_partial_sboxes(Fp* cells) {
  cells[0] = sbox(cells[0]);
}

__device__ void multiply_by_m_int(const Fp* M_INT_DIAG, Fp* cells) {
  // Exploit the fact that off-diagonal entries of M_INT are all 1.
  Fp sum = 0;
  for (uint i = 0; i < CELLS; i++) {
    sum += cells[i];
  }
  for (uint i = 0; i < CELLS; i++) {
    cells[i] = sum + M_INT_DIAG[i] * cells[i];
  }
}

__device__ void multiply_by_4x4_circulant(Fp* x) {
  // See appendix B of Poseidon2 paper.
  Fp t0 = x[0] + x[1];
  Fp t1 = x[2] + x[3];
  Fp t2 = Fp(2) * x[1] + t1;
  Fp t3 = Fp(2) * x[3] + t0;
  Fp t4 = Fp(4) * t1 + t3;
  Fp t5 = Fp(4) * t0 + t2;
  Fp t6 = t3 + t5;
  Fp t7 = t2 + t4;
  x[0] = t6;
  x[1] = t5;
  x[2] = t7;
  x[3] = t4;
}

__device__ void multiply_by_m_ext(Fp* old_cells) {
  // Optimized method for multiplication by M_EXT.
  // See appendix B of Poseidon2 paper for additional details.
  Fp cells[CELLS];
  for (uint i = 0; i < CELLS; i++) {
    cells[0] = 0;
  }
  Fp tmp_sums[4];
  for (uint i = 0; i < 4; i++) {
    tmp_sums[i] = 0;
  }
  for (uint i = 0; i < CELLS / 4; i++) {
    multiply_by_4x4_circulant(old_cells + i * 4);
    for (uint j = 0; j < 4; j++) {
      Fp to_add = old_cells[i * 4 + j];
      tmp_sums[j] += to_add;
      cells[i * 4 + j] += to_add;
    }
  }
  for (uint i = 0; i < CELLS; i++) {
    old_cells[i] = cells[i] + tmp_sums[i % 4];
  }
}

__device__ void full_round(const Fp* ROUND_CONSTANTS, Fp* cells, uint round) {
  add_round_constants_full(ROUND_CONSTANTS, cells, round);
  do_full_sboxes(cells);
  multiply_by_m_ext(cells);
}

__device__ void
partial_round(const Fp* ROUND_CONSTANTS, const Fp* M_INT_DIAG, Fp* cells, uint round) {
  add_round_constants_partial(ROUND_CONSTANTS, cells, round);
  do_partial_sboxes(cells);
  multiply_by_m_int(M_INT_DIAG, cells);
}

__device__ void poseidon2_mix(const Fp* ROUND_CONSTANTS, const Fp* M_INT_DIAG, Fp* cells) {
  uint round = 0;

  // First linear layer.
  multiply_by_m_ext(cells);

  // Do initial full rounds
  for (uint i = 0; i < ROUNDS_HALF_FULL; i++) {
    full_round(ROUND_CONSTANTS, cells, round);
    round++;
  }
  // Do partial rounds
  for (uint i = 0; i < ROUNDS_PARTIAL; i++) {
    partial_round(ROUND_CONSTANTS, M_INT_DIAG, cells, round);
    round++;
  }
  // Do remaining full rounds
  for (uint i = 0; i < ROUNDS_HALF_FULL; i++) {
    full_round(ROUND_CONSTANTS, cells, round);
    round++;
  }
}

} // namespace poseidon2

__global__ void poseidon2_fold(const Fp* ROUND_CONSTANTS,
                               const Fp* M_INT_DIAG,
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
  poseidon2::poseidon2_mix(ROUND_CONSTANTS, M_INT_DIAG, cells);
  for (uint i = 0; i < CELLS_OUT; i++) {
    output[gid * CELLS_OUT + i] = cells[i];
  }
}

__global__ void poseidon2_rows(const Fp* ROUND_CONSTANTS,
                               const Fp* M_INT_DIAG,
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
    cells[used++] = matrix[i * count + gid];
    if (used == CELLS_RATE) {
      poseidon2::poseidon2_mix(ROUND_CONSTANTS, M_INT_DIAG, cells);
      used = 0;
    }
  }
  if (used != 0 || count == 0) {
    // Zero pad to get a CELLS_RATE-aligned number of inputs
    for (uint i = used; i < CELLS_RATE; i++) {
      cells[i] = 0;
    }
    poseidon2::poseidon2_mix(ROUND_CONSTANTS, M_INT_DIAG, cells);
  }
  for (uint i = 0; i < CELLS_OUT; i++) {
    out[CELLS_OUT * gid + i] = cells[i];
  }
}
