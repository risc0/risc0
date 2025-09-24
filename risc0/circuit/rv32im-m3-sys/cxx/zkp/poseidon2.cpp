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

#include <array>
#include <iostream>

#include "zkp/poseidon2.h"
#include "zkp/poseidon2_consts.h"

namespace risc0 {

namespace p2impl {

cells_t add_round_constants_partial(const cells_t& in, size_t round) {
  cells_t out = in;
  out[0] += ROUND_CONSTANTS[round * CELLS];
  return out;
}

cells_t add_round_constants_full(const cells_t& in, size_t round) {
  cells_t out = in;
  for (size_t i = 0; i < CELLS; i++) {
    out[i] += ROUND_CONSTANTS[round * CELLS + i];
  }
  return out;
}

std::array<Fp, 4> multiply_by_4x4_circulant(const std::array<Fp, 4>& in) {
  const Fp circ_factor_2 = 2;
  const Fp circ_factor_4 = 4;
  Fp t0 = in[0] + in[1];
  Fp t1 = in[2] + in[3];
  Fp t2 = circ_factor_2 * in[1] + t1;
  Fp t3 = circ_factor_2 * in[3] + t0;
  Fp t4 = circ_factor_4 * t1 + t3;
  Fp t5 = circ_factor_4 * t0 + t2;
  Fp t6 = t3 + t5;
  Fp t7 = t2 + t4;
  return {t6, t5, t7, t4};
}

cells_t multiply_by_m_int(const cells_t& in) {
  // Exploit the fact that off-diagonal entries of M_INT are all 1.
  Fp sum = 0;
  cells_t out{};
  for (size_t i = 0; i < CELLS; i++) {
    sum += in[i];
  }
  for (size_t i = 0; i < CELLS; i++) {
    out[i] = sum + M_INT_DIAG_HZN[i] * in[i];
  }
  return out;
}

cells_t multiply_by_m_ext(const cells_t& in) {
  // Optimized method for multiplication by M_EXT.
  // See appendix B of Poseidon2 paper for additional details.
  cells_t out{};
  std::array<Fp, 4> tmp_sums{};
  for (size_t i = 0; i < CELLS / 4; i++) {
    std::array<Fp, 4> chunk{in[4 * i], in[4 * i + 1], in[4 * i + 2], in[4 * i + 3]};
    chunk = multiply_by_4x4_circulant(chunk);
    for (size_t j = 0; j < 4; j++) {
      tmp_sums[j] += chunk[j];
      out[4 * i + j] += chunk[j];
    }
  }
  for (size_t i = 0; i < CELLS; i++) {
    out[i] += tmp_sums[i % 4];
  }
  return out;
}

cells_t multiply_by_m_ext_naive(const cells_t& in) {
  cells_t out{};
  for (size_t i = 0; i < CELLS; i++) {
    Fp tot = 0;
    for (size_t j = 0; j < CELLS; j++) {
      tot += _M_EXT[i * CELLS + j] * in[j];
    }
    out[i] = tot;
  }
  return out;
}

Fp sbox2(Fp in) {
  Fp in2 = in * in;
  Fp in4 = in2 * in2;
  Fp in6 = in4 * in2;
  Fp in7 = in6 * in;
  return in7;
}

cells_t full_poseidon2_round(const cells_t& in, size_t idx) {
  cells_t out = add_round_constants_full(in, idx);
  for (size_t i = 0; i < CELLS; i++) {
    out[i] = sbox2(out[i]);
  }
  return multiply_by_m_ext(out);
}

cells_t partial_poseidon2_round(const cells_t& in, size_t idx) {
  cells_t out = add_round_constants_partial(in, idx);
  out[0] = sbox2(out[0]);
  return multiply_by_m_int(out);
}

cells_t poseidon2_mix(const cells_t& in) {
  cells_t cur = in;
  size_t idx = 0; // aka `round`

  // First linear layer.
  cur = multiply_by_m_ext(cur);

  for (size_t i = 0; i < ROUNDS_HALF_FULL; i++) {
    cur = full_poseidon2_round(cur, idx++);
  }
  for (size_t i = 0; i < ROUNDS_PARTIAL; i++) {
    cur = partial_poseidon2_round(cur, idx++);
  }
  for (size_t i = 0; i < ROUNDS_HALF_FULL; i++) {
    cur = full_poseidon2_round(cur, idx++);
  }

  return cur;
}

// TODO: Many of these are basically just renames due to differing naming conventions
void poseidonMultiplyByMExt(cells_t& cells) {
  cells = multiply_by_m_ext(cells);
}

void poseidonDoExtRound(cells_t& cells, size_t idx) {
  if (idx >= ROUNDS_HALF_FULL) {
    idx += ROUNDS_PARTIAL;
  };
  cells = full_poseidon2_round(cells, idx);
}

void poseidonDoIntRounds(cells_t& cells) {
  size_t idx = ROUNDS_HALF_FULL;
  for (size_t i = 0; i < ROUNDS_PARTIAL; i++) {
    cells = partial_poseidon2_round(cells, idx++);
  }
}

void poseidonSponge(cells_t& cells) {
  cells = poseidon2_mix(cells);
}

} // namespace p2impl

Digest poseidon2Hash(const Fp* data, size_t size, size_t stride) {
  using namespace p2impl;
  cells_t cur = {0};
  size_t curUsed = 0;
  for (size_t i = 0; i < size; i++) {
    cur[curUsed++] = data[i * stride];
    if (curUsed == 16) {
      cur = poseidon2_mix(cur);
      curUsed = 0;
    }
  }
  if (curUsed != 0 || size == 0) {
    // If `size` is not an even multiple of 16, zero-pad
    for (size_t loc = curUsed; loc < 16; loc++) {
      cur[loc] = 0;
    }
    cur = poseidon2_mix(cur);
  }
  Digest out;
  for (size_t i = 0; i < 8; i++) {
    out.words[i] = cur[i].asRaw();
  }
  return out;
}

Digest poseidon2HashPair(Digest x, Digest y) {
  using namespace p2impl;
  cells_t cur = {0};
  for (size_t i = 0; i < 8; i++) {
    cur[i] = Fp::fromRaw(x.words[i]);
    cur[8 + i] = Fp::fromRaw(y.words[i]);
  }
  cur = poseidon2_mix(cur);
  Digest out;
  for (size_t i = 0; i < 8; i++) {
    out.words[i] = cur[i].asRaw();
  }
  return out;
}

} // namespace risc0
