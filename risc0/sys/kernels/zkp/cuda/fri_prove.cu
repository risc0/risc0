// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include <assert.h>

#include "kernels.h"
#include "fp.h"


__global__ void fri_prove_values(uint32_t* out_values,
                                 const size_t values_column_width,
                                 uint32_t* positions,
                                 const size_t positions_len,
                                 struct CudaMerkleTreeProver* trees,
                                 const size_t trees_len,
                                 uint32_t* groups)
{
    size_t values_len = values_column_width * positions_len * trees_len;
    size_t idx = blockDim.x * blockIdx.x + threadIdx.x;

    if (idx < values_len) {
        size_t pos_idx = (idx / values_column_width / trees_len) % positions_len;
        size_t tree_idx = (idx / values_column_width) % trees_len;

        struct CudaMerkleTreeProver *tree = &trees[tree_idx];
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
}

__global__ void fri_prove_digests(uint32_t* out_digests,
                                  const size_t digests_column_width,
                                  uint32_t* positions,
                                  const size_t positions_len,
                                  struct CudaMerkleTreeProver* trees,
                                  const size_t trees_len,
                                  uint32_t* groups)
{
    size_t digests_len = digests_column_width * positions_len * trees_len;
    size_t idx = blockDim.x * blockIdx.x + threadIdx.x;

    if (idx < digests_len) {
        size_t pos_idx = (idx / digests_column_width / trees_len) % positions_len;
        size_t tree_idx = (idx / digests_column_width) % trees_len;

        struct CudaMerkleTreeProver *tree = &trees[tree_idx];
        uint32_t pos = positions[pos_idx] % groups[tree_idx];
        assert(pos < tree->row_size);

        pos += tree->row_size;

        size_t digest_chunk_idx = idx % digests_column_width;

        if (digest_chunk_idx == 0) {
            out_digests[idx] = (32 - __clz(pos / tree->top_size) - 1) * 8;
        } else {
            size_t digest_chunk = (digest_chunk_idx - 1) % 8;
            size_t digest_idx = (digest_chunk_idx - 1) / 8;
            size_t i = pos / pow(2, digest_idx);
            if (i >= 2 * tree->top_size) {
                size_t low_bit = i % 2;
                size_t other_digest_idx = 2 * (i / 2) + (1 - low_bit);
                out_digests[idx] = tree->nodes[other_digest_idx * 8 + digest_chunk];
            }
        }
    }
}
