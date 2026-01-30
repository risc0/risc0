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
#include "sha256.h"

using namespace metal;

kernel void sha_rows(device ShaDigest* out,
                     const device Fp* matrix,
                     const device uint32_t& count,
                     const device uint32_t& col_size,
                     uint gid [[thread_position_in_grid]]) {
  out[gid] = shaHash(matrix + gid, col_size, count);
}

kernel void sha_fold(device ShaDigest* out,
                     const device ShaDigest* in,
                     uint gid [[thread_position_in_grid]]) {
  out[gid] = shaHashPair(in[2 * gid], in[2 * gid + 1]);
}
