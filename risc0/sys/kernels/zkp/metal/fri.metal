// Copyright 2026 Risc0, Inc.
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
#include "fpext.h"

using namespace metal;

constant size_t kFriFold = 16;

/// Compute `ceil(log_2(in))`, i.e. find the smallest value `out` such that `2^out >= in`.
inline constexpr size_t log2Ceil(size_t in) {
  size_t r = 0;
  while ((1 << r) < in) {
    r++;
  }
  return r;
}

kernel void fri_fold(device Fp* out,
                     const device Fp* in,
                     const device FpExt& mix,
                     const device uint32_t& count,
                     uint gid [[thread_position_in_grid]]) {
  FpExt tot;
  FpExt curMix(1);
  for (uint32_t i = 0; i < kFriFold; i++) {
    size_t rev_i = reverse_bits(i) >> (32 - log2Ceil(kFriFold));
    size_t rev_idx = rev_i * count + gid;
    FpExt factor(in[0 * count * kFriFold + rev_idx],
               in[1 * count * kFriFold + rev_idx],
               in[2 * count * kFriFold + rev_idx],
               in[3 * count * kFriFold + rev_idx]);
    tot += curMix * factor;
    curMix *= mix;
  }
  for (size_t i = 0; i < 4; i++) {
    out[count * i + gid] = tot.elems[i];
  }
}

struct MetalMerkleTreeProver {
    size_t row_size;
    size_t col_size;
    size_t top_size;
    const device uint32_t *matrix;
    const device uint32_t *nodes;
};

kernel void fri_prove_values(device uint32_t* out_values,
                             const device size_t& values_column_width,
                             device uint32_t* positions,
                             const device size_t& positions_len,
                             const device struct MetalMerkleTreeProver* trees,
                             const device size_t& trees_len,
                             device uint32_t* groups,
                             uint idx_in [[thread_position_in_grid]]) {
    size_t idx = idx_in;
    size_t pos_idx = (idx / values_column_width / trees_len) % positions_len;
    size_t tree_idx = (idx / values_column_width) % trees_len;

    const device struct MetalMerkleTreeProver *tree = &trees[tree_idx];
    uint32_t pos = positions[pos_idx] % groups[tree_idx];
    assert(pos < tree->row_size);

    size_t c = idx % values_column_width;
    if (c < tree->col_size + 1) {
        if (c == 0) {
            out_values[idx] = tree->col_size;
        } else {
            out_values[idx] = tree->matrix[pos + (c - 1) * tree->row_size];
        }
    }
}

kernel void fri_prove_digests(device uint32_t* out_digests,
                              const device size_t& digests_column_width,
                              device uint32_t* positions,
                              const device size_t& positions_len,
                              const device struct MetalMerkleTreeProver* trees,
                              const device size_t& trees_len,
                              device uint32_t* groups,
                              uint idx_in [[thread_position_in_grid]]) {
    size_t idx = idx_in;
    size_t pos_idx = (idx / digests_column_width / trees_len) % positions_len;
    size_t tree_idx = (idx / digests_column_width) % trees_len;

    const device struct MetalMerkleTreeProver *tree = &trees[tree_idx];
    uint32_t pos = positions[pos_idx] % groups[tree_idx];
    assert(pos < tree->row_size);

    pos += tree->row_size;

    size_t digest_chunk_idx = idx % digests_column_width;

    if (digest_chunk_idx == 0) {
        out_digests[idx] = (32 - clz(pos / (uint32_t)tree->top_size) - 1) * 8;
    } else {
        size_t digest_chunk = (digest_chunk_idx - 1) % 8;
        size_t digest_idx = (digest_chunk_idx - 1) / 8;
        size_t i = pos >> digest_idx;
        if (i >= 2 * tree->top_size) {
            size_t low_bit = i % 2;
            size_t other_digest_idx = 2 * (i / 2) + (1 - low_bit);
            out_digests[idx] = tree->nodes[other_digest_idx * 8 + digest_chunk];
        }
    }
}
